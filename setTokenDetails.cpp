//Find and Set Token Details Function
//It finds the tokens that we are looking for
//It will output the token, its type and width
void TokenList::findAndSetTokenDetails(Token *token)
{
    string tokenString = token->stringRep; //tokenString will get us the the string of the token we are looking at
    int widthCounter = 0; // a counter to output the width of the token

    if(token == NULL)//If list is empty, that means there are no tokens
    {
        return;
    }

    for(unsigned int i = 0; i< tokenString.length(); i++)//changes the whole string to lower case
    {
        tokenString[i]= tolower(tokenString[i]);
    }

    if(token->prev && token->prev->stringRep == "--")//This will identify when a comment starts and its body
    {
        token->setTokenType(T_CommentBody);
        return;
    }

    if(tokenString == "true" || tokenString == "false")//This will identify a boolean variable and set its type to a literal and width 1
    {
        token->setTokenType(T_Literal);
        token->setTokenDetails("boolean", 1);
        return;
    }
    else if(tokenString[0] >= '0' && tokenString[0] <= '9')//This will identify an integer, it will set its type to literal and width 0
    {
        token->setTokenType(T_Literal);
        token->setTokenDetails("integer", 0);
        return;
    }
    else if(tokenString[0] == '\'')//This will identify an ', it will set its type to literal and width 0
    {
        token->setTokenType(T_Literal);
        token->setTokenDetails("std_logic", 1);
        return;
    }
    else if (tokenString[0] == '"')//This will identify an ", it will set its type to literal
    {
        token->setTokenType(T_Literal);//it will set the type of the token to a literal
        widthCounter = tokenString.length() - 2;//its token length will be anything -2
        token->setTokenDetails("std_logic_vector", widthCounter);//This will be assigned to standard logic vector
        return;
    }
    else//This case if for Hexa, octal and binary number
    {
        if(tokenString[0] == 'x' || tokenString[0] == 'b' || tokenString[0] == 'o')//checks if the first token is a x=hexadecimal, b= binary and o = octal
        {
            if(tokenString[1] == '"')//If the second token right after it is a quotation
            {
                if(tokenString[2] >= '0' && tokenString[2] <= '9')//If the third token is an integer
                {
                    token->setTokenType(T_Literal);        //then set its type to literal
                    widthCounter = tokenString.length() - 3;//we have the width -3 because we start at position 3

                    if(tokenString[0] == 'x')//If it is a hexadecmial then it contains 4 bits
                    {
                        widthCounter = widthCounter*4;
                    }
                    else if(tokenString[0] == 'o')//If it is a octal then it contains 3 bits
                    {
                        widthCounter = widthCounter*3;
                    }
                    else{}

                    token->setTokenDetails("std_logic_vector", widthCounter);//then set it to standard logic vector and its width according to widthCounter

                    return;
                }
            }
        }
    }

    for (unsigned int i =0 ; i < sizeof(str_operators)/sizeof(string);i++)// This for loop is to identify an operator and then set its type to operator
    {
        if (tokenString == str_operators [i])//I am comparing the token with the string of operators above
        {
            token->setTokenType(T_Operator);
            token ->setTokenDetails("Type_Operator ",0);//the width will be zero
            return;
        }
    }

    for(unsigned int k = 0; k < sizeof(str_keywords)/sizeof(string); k++)// This for loop is to identify a keyword and then set its type to identifier
     {
        if(tokenString == str_keywords[k])//I am comparing the token with the string of keywords above
         {
            token->setTokenType(T_Identifier);
            token->setKeyword();
            token->setTokenDetails("keyword", 0);// the width will be zero
            return;
         }
     }

    //This nested for loop checks if it is a character only then its type will be identifier
    for(unsigned int i =0 ; i < tokenString.length();i++)
    {
        for(unsigned int j = 0; j < str_char.length(); j++)
        {
            if (tokenString[i] == str_char[j])
            {
                token->setTokenType(T_Identifier);//Setting the type of the character to Identifier

                if (tokens_type.head != NULL)//if the first token in the tokenlist is not equal to NULL
                {

                    Token* to_token = tokens_type.getFirst();// creating a pointer called to_token, which gets the first token of a specific type

                    while (to_token)
                    {
                        string identifier = token->getStringRep();//I am getting the string in the list and putting it to identifier

                        for(unsigned int i = 0; i< identifier.length(); i++)//changes the string that is in identifier to lower case
                        {
                            identifier[i]= tolower(identifier[i]);
                        }

                        if (to_token->getStringRep() == identifier)// If the type of token in the string turns out to be an identifier
                        {                                          // Then call in the function setTokenDetails and output the type and width of the token
                            token->setTokenDetails(to_token->getTokenDetails()->type,to_token->getTokenDetails()->width);

                            return;
                        }

                        to_token = to_token->getNext();//This will keep going through the list to get the next token
                    }
                }

                token->setTokenDetails("Type_Identifier",0);//it will set the token details to identifier and width 0
                string tokenLower_Case = token->getStringRep();
                for(unsigned int i = 0; i< tokenLower_Case.length(); i++)//changes it to lower case
                {
                    tokenLower_Case[i]= tolower(tokenLower_Case[i]);
                }

                //This creates the subsystem to know if the is one of these std.logic or std.logic.vector or signed or unsigned...
                //It then sets its type to identifier and width according to the length
                if (tokenLower_Case == "std_logic"|| tokenLower_Case== "std_logic_vector" ||tokenLower_Case== "signed" || tokenLower_Case == "unsigned"|| tokenLower_Case == "integer" || tokenLower_Case == "boolean"|| tokenLower_Case == "character"|| tokenLower_Case =="string")
                {

                 token->setTokenType(T_Identifier);
                 token->setTokenDetails("type",token->getStringRep().length());
                 find_type(token);
                }

                return;
            }
        }
    }

    token->setTokenType(T_Other);// else the token type will be other
    token->setTokenDetails("Type_other",0);//the width of other is zero and it will output "type_other" for its type
    return;
}

//This function find type 2, finds the variable and the width of the variable that is signed, unsigned, std_logic, std_logic vector
void find_type(Token *token)
{
   string type = token->getStringRep(); //This will get the string in token and put it in type
   Token *p_token = token;//This is a pointer I will be using to point to the token in the list
   bool flag = true;//To know if the list is complete
   Token *toToken;

   while(flag)//If flag is true, the list is complete
   {
      if (p_token->getTokenType() == 1 && (p_token->getStringRep() != type) && !(p_token->isKeyword()))//if tokentype is an identifier and its is not equal to a type
      {                                                                                                //and its is not a keyword
         if (token->getNext()->getStringRep() == "(")//This checks if the next token is a bracket
         {
            string identifier = p_token->getStringRep();//This gets the string and puts it in identifier
            int num1 = stoi(token->getNext()->getNext()->getStringRep(),NULL,10);//this changes the string to integer
            int num2 = stoi(token->getNext()->getNext()->getNext()->getNext()->getStringRep(),NULL,10);//This changes the string to integer
            int width = abs(num1 - num2) + 1;//This will output the width of the variable according to what it is declared to
            p_token->setTokenDetails(type,width);//This will call in the function setTokenDetials and assign its type and width

            for(unsigned int i = 0; i< identifier.length(); i++)//changes it to lower case
            {
                identifier[i]= tolower(identifier[i]);
            }

            tokens_type.append(identifier); //We are taking the variable and putting it in a universal list to keep track of its type
            toToken = tokens_type.getLast();//The last is always changing when you append, so we are always pointing to a new last
            toToken->setTokenDetails(type,width);
         }
         else
         {
            string identifier = p_token->getStringRep();//will get the string and put it in identifier

            for(unsigned int i = 0; i< identifier.length(); i++)//changes it to lower case
            {
                identifier[i]= tolower(identifier[i]);
            }

            tokens_type.append(identifier);//We are taking the variable and putting it in a universal list to keep track of its type
            toToken = tokens_type.getLast();//The last is always changing when you append, so we are always pointing to a new last

            if(type == "integer")//If the type is an integer, width will equal to zero, and set its type to integer
            {
                p_token->setTokenDetails(type,0);
                toToken->setTokenDetails(type,0);
            }
            else//If it is not an intger, then it will have width  1
            {
                p_token->setTokenDetails(type,1);
                toToken->setTokenDetails(type,1);
            }
         }
      }

      string tokenLowerCase = p_token->getStringRep();
      for(unsigned int i = 0; i< tokenLowerCase.length(); i++)//changes it to lower case
        {
            tokenLowerCase[i]= tolower(tokenLowerCase[i]);
        }

      if(tokenLowerCase== "port")//This means that there are still tokens left in the variable, keep going, we are not at the end
      {
        flag = false;

      }
      else if (p_token ->getStringRep() ==";")//This means that there are still tokens left in the variable, keep going, we are not at the end
      {
       flag = false;
      }
      else if (tokenLowerCase=="signal")//This means that there are still tokens left in the variable, keep going, we are not at the end
      {
        flag = false;
      }
      else if (tokenLowerCase == "variable")//This means that there are still tokens left in the variable, keep going, we are not at the end
      {
        flag = false;
      }
      else
      {
         p_token = p_token->getPrev();//This will keep getting the previous token
      }
   }
}

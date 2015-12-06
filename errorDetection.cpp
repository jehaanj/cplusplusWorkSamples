//This function will output the type and width mismatches
void find_number_of_type_width_mismatches(const TokenList &jacob)
{
    TokenList* conditional_tokens = findAllConditionalExpressions(jacob);//This is a list that contains all the conditional expressions
    Token* pto_token = conditional_tokens->getFirst();
    string literalType; //This string will contain the literal type
    int literalWidth;   //This integer will contain the literal width
    string identifierType;
    int identifierWidth;

    int num_type_mismatch = 0;//This is a counter for the number of type misMatches
    int num_width_mismatch = 0;//This is a counter for the number of width misMatches

    while(pto_token != NULL)//This checks if there is tokens in the list
    {
        if(pto_token->getTokenType() == 2)//If the token type is a litreal
        {
            literalType = pto_token->getTokenDetails()->type;//Litreal type
            literalWidth = pto_token->getTokenDetails()->width;//Litreal width
            identifierType = pto_token->getPrev()->getPrev()->getTokenDetails()->type;//Identifier type
            identifierWidth = pto_token->getPrev()->getPrev()->getTokenDetails()->width;//Identifier width

            for(unsigned int i = 0; i< literalType.length(); i++)//changes it to lower case
            {
                literalType[i]= tolower(literalType[i]);
            }

            for(unsigned int i = 0; i< identifierType.length(); i++)//changes it to lower case
            {
                identifierType[i]= tolower(identifierType[i]);
            }

            if(literalType != identifierType)//Checks for a type mismatch
            {
                num_type_mismatch++;
            }
            else if (literalWidth != identifierWidth)//Checks for a width Mismatch
            {
                num_width_mismatch++;
            }

          pto_token = pto_token->getNext();//This will keep getting the next token in the list
        }
        else//If it is not a literal
        {
            pto_token = pto_token->getNext();
        }
    }
    cout << "The number of type mismatches " << num_type_mismatch << endl;
    cout << "The number of width mismatches " << num_width_mismatch << endl;
}

//This function is to output the line that contains the error type
void print_type_width_mismatch_lines(const TokenList &jacob)
{
    TokenList *error_conditional_tokens = findAllConditionalExpressions(jacob);//This will put the list of conditional expressions into error_conditional_tokens
    TokenList coditional_list;//This is an empty list
    Token*p_tokens = error_conditional_tokens->getFirst();
    while(p_tokens != NULL)//This checks if the list is not empty
    {
      coditional_list.append(p_tokens);//We are copying the tokens and putting them into the new empty list
      p_tokens = p_tokens ->getNext();//We are going through the list
    }

    Token* error_pointer = coditional_list.getFirst();//This will get the first token in the list
    string errorliteralType;//A string that will contain the literal error type
    string erroridentifierType;//A string that will contain the error identifier type
    int errorliteralWidth;//An integer that will contain the error literal width
    int erroridentifierWidth;//An identifier that will contain the error identifier width

    while(error_pointer != NULL)//checks if the list is not emtpy
    {
        if(error_pointer->getTokenType() == 2)//Checks if it a literal
        {
                errorliteralType = error_pointer->getTokenDetails()->type;
                erroridentifierType = error_pointer->getPrev()->getPrev()->getTokenDetails()->type;
                errorliteralWidth = error_pointer->getTokenDetails()->width;
                erroridentifierWidth = error_pointer->getPrev()->getPrev()->getTokenDetails()->width;

                for(unsigned int i = 0; i< errorliteralType.length(); i++)//changes it to lower case
                {
                    errorliteralType[i]= tolower(errorliteralType[i]);
                }

                for(unsigned int i = 0; i< erroridentifierType.length(); i++)//changes it to lower case
                {
                    erroridentifierType[i]= tolower(erroridentifierType[i]);
                }

                if(errorliteralType != erroridentifierType)//This checks for type error
                {
                    Token * pon_token;
                    pon_token = error_pointer;

                    while( pon_token->getPrev()!= coditional_list.getFirst()->getPrev())//This while loop goes to identify were the start of the line is
                     {
                        pon_token = pon_token->getPrev();//jkeep going back
                        if(pon_token->getPrev()->getStringRep() == "\\n")//This is the start of the line
                        {
                            break;
                        }
                     }

                    cout << "Error: Type Mismatch" << endl;

                    while(pon_token->getStringRep() != "\\n")
                    {
                      cout << pon_token->getStringRep() << " ";
                      pon_token = pon_token->getNext();
                    }

                    cout << endl << endl;

                }
                else if (errorliteralWidth != erroridentifierWidth)//this is for error width
                {
                      Token* pon2_token;
                      pon2_token = error_pointer;
                     while( pon2_token->getPrev()!= coditional_list.getFirst()->getPrev())//This keeps going back to identify where the start is
                     {
                        if(pon2_token->getPrev()->getStringRep() == "\\n")//The start is here
                        {
                            break;
                        }

                        pon2_token = pon2_token->getPrev();
                     }

                    cout << "Error Type: Width Mismatch" << endl;

                    while(pon2_token->getStringRep() != "\\n")
                    {
                        cout << pon2_token->getStringRep() << " ";
                      pon2_token = pon2_token->getNext();
                    }

                    cout << endl << endl;
                }
          error_pointer = error_pointer->getNext();
        }
        else
        {

            error_pointer = error_pointer->getNext();
        }

    }
}

//This function will find the number of End Ifs that are missing and
//Will output the number of missing End-If's
void find_number_of_missing_endifs(const TokenList &jacob)
{
    Token* all_list = jacob.getFirst();//This will contain the list Jacob which contains the list of the tokenList
    int num_if(0),num_endif(0);//Two counters

    while (all_list)//as long as the list is not empty
    {
        string token_string = all_list->getStringRep();
        string token_end;
        if(all_list ->getNext() != NULL)//This get the next token as long as it is not NULL
        {
            token_end = all_list->getNext()->getStringRep();//This will get the next string and assign it to token_end
        }
        else//The next token is NULL
        {
           break;
        }

        for(unsigned int i = 0; i< token_string.length(); i++)//changes it to lower case
         {
            token_string[i]= tolower(token_string[i]);
         }
         for(unsigned int i = 0; i< token_end.length(); i++)//changes it to lower case
         {
            token_end[i]= tolower(token_end[i]);
         }
        if(token_string == "if" && token_end != ";")//If you see an if and a ; after it, then add the number of if's
        {
          num_if++;
        }
        else if(token_string == "end" && token_end == "if")//if you see an end and an if after it, then add the number of endIfs
        {
          num_endif++ ;
        }
        all_list = all_list->getNext();// This will get the Next token
    }

    //We are comparing the number of if's and end if's
    if (num_if > num_endif)
    {
      cout << "The number of missing \"end if\"(s): " << num_if - num_endif << endl;
    }
    else if(num_endif > num_if)
    {
      cout << "then number of missing \"if\"(s): " << abs(num_if-num_endif) << endl;;
    }
    else
    {
        cout<<"There are no missing end ifs "<<endl;

    }
}

//This function will check for the number of missing Then's
void find_number_of_missing_thens(const TokenList &jacob)
{
    Token* all_list = jacob.getFirst();
    int num_if(0),num_then(0);// a counter to keep track of the number of if's and then's

    while (all_list)//as long as the list is not compelte
    {
        string token_string = all_list->getStringRep();
        string token_end;
        if(all_list ->getNext() != NULL)//as long as the next token is not NULL
        {
            token_end = all_list->getNext()->getStringRep();//get the next string
        }
        else//the next token is NULL
        {
           break;
        }

        for(unsigned int i = 0; i< token_string.length(); i++)//changes it to lower case
         {
            token_string[i]= tolower(token_string[i]);
         }
         for(unsigned int i = 0; i< token_end.length(); i++)//changes it to lower case
         {
            token_end[i]= tolower(token_end[i]);
         }
        if((token_string == "if" || token_string =="elsif") && token_end != ";")//if the token is if or elsif and a semicolon after one of those then add the number to if
        {
          num_if++;
        }
        else if(token_string == "if" || token_end == ";")
        {
            ///do nothing.
        }
        else if(token_string == "then")//Add the number of thens
        {
            num_then++;
        }
        all_list = all_list->getNext();
    }

    //this will compare the number of then's and if's
    if (num_if > num_then)
    {
      cout << "The number of missing \"then\"(s): " << num_if - num_then << endl;
    }
    else if(num_then > num_if)
    {
      cout << "then number of missing \"if\"(s): " << abs(num_then-num_if) << endl;;
    }
    else
    {
        cout<<"There are no missing thens "<<endl;
    }
}

//This function will output the number of tokens and the number of conditional expressions
void find_number_tokens_and_conditions(const TokenList &jacob)
{
    Token* Count = jacob.getFirst();//This will get the first token in the list
    int Number_of_tokens = 0;//This is a counter

    while(Count != NULL)//As long as the there is tokens in the list
    {
        Number_of_tokens++;
        Count=Count->getNext();
    }

    cout<<"The number of tokens: "<<Number_of_tokens<<endl;//To output the number of tokens
    cout << "The number of conditional expressions " << Conditional_line_counter<< endl;//To output the number of conditional expressions
}

//This function is to output the block of code that is missing an "end if" statement
void print_block_of_missing_end_if(const TokenList &jacob)
{
    Token * p_token = jacob.getFirst();//This will get the first token in the list
  while (p_token != NULL)//This checks if the list is not empty
  {
      string if_string = p_token->getStringRep();

      for(unsigned int i = 0; i<if_string.length(); i++)//changes it to lower case
      {
         if_string[i]= tolower(if_string[i]);
      }

      if (if_string == "if")//If the string is if
      {
         Token * Start = p_token;
         Token * END = p_token;
         while(END != NULL)//This checks if the list is not empty
         {
             string end_string = END->getStringRep();
             string if2_string = END->getNext()->getStringRep();

               for(unsigned int i = 0; i<end_string.length(); i++)//changes it to lower case
               {
                 end_string[i]= tolower(end_string[i]);
               }

               for(unsigned int i = 0; i<if2_string.length(); i++)//changes it to lower case
               {
                 if2_string[i]= tolower(if2_string[i]);
               }

                if(end_string == "end" && if2_string == "if")
                {
                    p_token = END->getNext()->getNext()->getNext();
                    break;
                }
               else if (end_string == "end" || ((end_string == "if")&& Start != END))//this checks for end if
               {
                  if (if2_string != "if")
                  {
                    while (Start != END)
                    {
                        if(Start->getPrev() != NULL)
                        {
                            if(Start->getPrev()->getStringRep() == ";" || Start->getPrev()->getStringRep() == "then")
                            {
                                cout << endl;
                            }
                        }
                        cout << Start->getStringRep() << " ";
                        Start = Start ->getNext();
                    }
                    cout << endl<<"there is an endif missing"<<endl;
                    p_token = END->getNext()->getNext();
                    break;
                  }
                  else
                  {
                    p_token = END->getNext()->getNext();
                    break;
                  }
               }
               END = END->getNext();
         }
      }
      else
      {
        p_token = p_token->getNext();//This will keep going till you find a then
      }

  }
}

//This function will output the line that contains the missing "Then"
void output_line_of_missing_then(const TokenList &jacob)
{
    TokenList* conditionalList = findAllConditionalExpressions(jacob);//This will bring the list from findAllContionalExpression
    Token *cursor = conditionalList->getFirst();


    while(cursor != NULL)//This checks if the list is empty
    {
        string endline = cursor->getStringRep();

        if(endline == "\\n")//This checks where the line ends
        {
            Token *prevToken = cursor->getPrev();

            if(prevToken->getStringRep() == ")"){} //if a bracket or
            else if(prevToken->getStringRep() == "\\n"){}  //another endline is found, nothing should be done, else
            else
            {
                Token *lastBracket;
                Token *firstBracket;

                lastBracket = prevToken;

                while(lastBracket->getStringRep() != ")")           //a pointer is set to the end of the line with the missing "then"
                {
                    //cout << lastBracket->getStringRep() << endl;
                    lastBracket = lastBracket->getPrev();
                }

                //cout << lastBracket->getStringRep() << endl;

                firstBracket = lastBracket;



                while( firstBracket->getPrev() != NULL)                                             //another pointer is set
                {                                                                                   //to find the beginning
                   string if_string = firstBracket->getPrev()->getStringRep();                      //of the line with the missing "then

                    for(unsigned int i = 0; i<if_string.length(); i++)//changes it to lower case
                         {
                            if_string[i]= tolower(if_string[i]);
                         }
                    if (if_string == "if")
                    {
                     break;
                    }
                    if(firstBracket->getStringRep() == "\\n")
                    {
                        break;
                    }
                    firstBracket = firstBracket->getPrev();
                }

                //cout << "some shit 1" << endl;

                while(firstBracket != lastBracket->getNext())                                                   //everything between the two pointers
                {                                                                                               //is printed out
                    //cout << "some shit" << endl;
                    if(firstBracket != NULL)
                    {
                        //cout << endl;
                        if(firstBracket->getStringRep() == "\\n"||firstBracket->getStringRep() == "elsif"){}
                        else
                        {
                            cout << firstBracket->getStringRep() << " ";
                        }
                    }
                    firstBracket = firstBracket->getNext();
                }
                cout << endl;
                //cursor = cursor->getNext();
            }
        }

    cursor = cursor->getNext();
    }
}

//This function is prepares the token to be tokanized
//It would go through a string and tokanize it according to the rules we have set
void Tokenizer::prepareNextToken()
{
    string tokenString = *str;  //This is a pointer that will contain the token string
    string alphaNumeric =  "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    size_t endToken;

    offset = tokenString.find_first_not_of ("\n\t ",offset); //This will find the first position that is not whitespace
                                                             //It will then move through it
    if ( str == NULL || offset >= tokenString.length())//Checks if the list is empty, that means nothing to tokanize
    {                                                  //Returns true if it is empty
        complete = true;
    }

    if (comment)//this will check if the next token is a comment
    {
        tokenLength = tokenString.length()  - offset; //taking the whole comment as one token
    }

    else if(tokenString[offset]=='-')//This will take - as a delimiter of size one
    {
        if (offset+2 < tokenString.length() && tokenString[offset+1]=='-')//for comment
        {
            tokenLength = 2;
            comment = true;
        }

        else //for the minus delimiter
        {
            tokenLength = 1;
        }
    }

    //If it is an = delimiter or => operator
    else if(tokenString[offset]=='=')
    {
        if (offset+2 < tokenString.length() && tokenString[offset+1]=='>')
        {
            tokenLength = 2;//if it is =>, then the length of the operator is 2
        }
        else
        {
            tokenLength = 1;// if it is =, then the length of the operator is 1
        }
    }

    //This case is for <> delimiter,equate its length to 2
    else if(tokenString[offset] == '<' &&(offset+2 < tokenString.length() && tokenString[offset+1] == '>'))
    {
        tokenLength = 2;
    }

    //This case is for > or < or / or : delimiters which have a length of 1
    else if(tokenString[offset]=='<'|| tokenString[offset]=='>'||tokenString[offset]=='/'||
            tokenString[offset]==':')
    {
        if (offset+2 < tokenString.length() && tokenString[offset+1]=='=')// for /=. :=, <=, >=
            {
                tokenLength = 2;//the length equals 2
            }
            else
            {
                tokenLength = 1;//the length equals 1
            }
    }
    //This is for single delimiters
    else if( tokenString[offset]=='+'||tokenString[offset]=='&'||tokenString[offset]==';'
            ||tokenString[offset]==','|| tokenString[offset]=='.'|| tokenString[offset]=='#'||
            tokenString[offset]=='|'||tokenString[offset]=='('|| tokenString[offset]==')')
        {
             tokenLength = 1;
        }
    //This case is for * delimiter
    else if(tokenString[offset]=='*')
    {
        if (offset+2 < tokenString.length() && tokenString[offset+1]=='*')// for **
        {
            tokenLength = 2;//The length is 2
        }
        else
        {
            tokenLength = 1;//The length is 1
        }
    }
    //This case is for "
    else if(tokenString[offset]=='"')
    {
        endToken = tokenString.find_first_of('"',offset+1);
        tokenLength = (endToken-offset)+1; // the +1 is to include all quotes
    }
    //This case is for "\"
    else if (tokenString[offset]=='\'')
    {
        if(offset+2 < tokenString.length() && tokenString[offset+2]=='\'')//this is for bit cases
            {tokenLength = 3;}
        else
        {tokenLength = 1;} //this is for just a single quote
    }
    //This case if it is a character big and small or a number with the _ ex: std_logic
    else if((tokenString[offset]>='a'&& tokenString[offset]<='z')||(tokenString[offset]>='A'&&
            tokenString[offset]<='Z')||tokenString[offset]=='_'||
            (tokenString[offset]>='0'&& tokenString[offset]<='9'))//alphanumerics
            {
            // case for either binary or octal or hex number.
            if((tokenString[offset]=='o'|| tokenString[offset]=='O'||tokenString[offset]=='x'||
                tokenString[offset]=='X'||tokenString[offset]=='b'||
                tokenString[offset]=='B') && (offset+2 < tokenString.length() && tokenString[offset+1]=='"'))
                {
                    endToken= tokenString.find_first_of("\"", offset+2);
                    tokenLength = (endToken - offset) + 1; // +1 isto include quote in token
                }
            //This will find the first thing that is not in the string of the aplhaNumeric
            else if(tokenString[tokenString.find_first_not_of(alphaNumeric,offset)]== '\'')
            {
                endToken = tokenString.find_first_not_of(alphaNumeric,offset);

                if(endToken+2 < tokenString.length() && tokenString[endToken+1]== ' ') //checks for complements
                {
                  endToken+=1;
                }
                else
                {
                endToken = tokenString.find_first_not_of(alphaNumeric,endToken+1); //special words in VHDL with ' in them
                }
                tokenLength = endToken - offset;
            }
           else
           {
                endToken = tokenString.find_first_not_of(alphaNumeric,offset);//if the are only alphanumerics
                tokenLength = endToken - offset;
           }
        }
    else
    {
        complete = true;//There is nothing to tokanize, list is complete
    }
 }

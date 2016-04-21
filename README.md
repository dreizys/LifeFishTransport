# LifeFishTransport
/*bool parsedCorrectly = 0;
        //characters = "";

        //Loop until we find the newline delimiter.
        do
        {
          //Get the line.
          QByteArray direct = arduino->readLine();//Line();

          //If we have found a new line character in any line, complete the parse.
          if(QString(direct).contains('\n'))
          {
              if(QString(direct) != "\n")
              {
                  characters += QString(direct);
                  characters.remove(QRegExp("[\\n\\t\\r]"));
                  parsedCorrectly = 1;
              }   
          }
          //If we don't find the newline straight away, add the string we got to the characters QString and keep going.
          else
              characters += QString(direct);
        }while(!parsedCorrectly);

        //Save characters to data and emit signal to collect it.
        data = characters;

        emit dataReady();

        //Reset characters!
        characters = "";
    }

    return 0;
}*/

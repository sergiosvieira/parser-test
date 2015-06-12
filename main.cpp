#include <iostream>
#include <cstdio>

using namespace std;

fpos_t read_single_line(FILE* input_fp, char ** buffer, unsigned int * buffer_len)
{
    long int original_pos = ftell(input_fp);
    long int current_pos  = original_pos;

    register int current_char = 0;

    /* Checking one character at a time until the end of a line is found */
    while(true)
    {
        current_char = fgetc(input_fp);

        if (current_char == EOF)
        {
            /* We have reached the end of the file */
            //more_rows = false;

            break;

        } else if (current_char =='\n')
        {
            /* We have reached the end of the row */
            current_pos++;

            break;

        } else {

            current_pos++;
        }
    }

    /* Let's try to peek one character ahead to see if we are at the end of the file */
    /**
    if (more_rows)
    {
        current_char = fgetc(input_fp);

        more_rows = (current_char == EOF) ? false : true;
    }
    **/
    /* Find out how long this row is */
    const size_t length_of_row = current_pos - original_pos;

    if (length_of_row > 0)
    {
        *buffer_len = length_of_row * sizeof(char) + 1;

        *buffer = (char *) realloc(*buffer, *buffer_len);

        memset(*buffer, 0, *buffer_len);

        /* Reset the internal pointer to the original position */
        fseek(input_fp, original_pos, SEEK_SET);

        /* Copy the contents of the line into the buffer */
        fread(*buffer, 1, length_of_row, input_fp);
    }
    return current_pos;
}

fpos_t readLine(FILE& a_file, char ** buffer, unsigned int * buffer_len)
{
    char currentChar = '\0';
    while ((currentChar = fgetc(&a_file)) != '\n'
           && currentChar != '\r'
           && !feof(&a_file))
    {
        //cout << "current char:" << currentChar << " codigo:" << int(currentChar) << "\n";
    }
    if (currentChar == '\r')
    {
        currentChar = fgetc(&a_file);
    }
    //cout << "last line char:" << currentChar << " codigo:" << int(currentChar) << "\n";
    return ftell(&a_file);
}

int main()
{
    FILE* file = fopen("CHUVAS.TXT", "r");
    if (file == nullptr)
    {
        cout << "Erro ao abrir o arquivo!\n";
    }
    else
    {
        cout << "Arquivo aberto com sucesso!\n";
        fpos_t currentPosition;
        do
        {
            unsigned int line_length = 0U;
            /* Character array buffer for the current record */
            char* line = nullptr;
            //currentPosition = readLine(*file, &line, &line_length);
            currentPosition = read_single_line(file, &line, &line_length);
            cout << "posicao:"<< currentPosition << "\n";
            if (line_length > 0)
            {
                //cout << "Line: " << line << " length:" << line_length << "\n";
                cout << line;
            }
        } while (!feof(file));
    }
    fclose(file);
    return 0;
}

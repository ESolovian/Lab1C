#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>


int main(int argc, char** argv) {
    size_t count_lines; //инициализация количества строк
    size_t count_words; //инициализация количества слов
    size_t size_file; //инициализация размера файла в байтах
    size_t average_size_line;
    bool lines = false; //параметры, которые вызывают соответствующие опции
    bool words = false;
    bool bytes = false;
    bool average_bytes = false;
    bool all = false; //без опций
    bool flag = true;
    std::string filename;

    //подключение параметров в зависимости от опций
    for (int i = 1; i < argc; i++){
        if (strcmp(argv[i], "--lines") == 0 || strcmp(argv[i], "-l") == 0){
            lines = true;
        }
        else if (strcmp(argv[i], "--words") == 0 || strcmp(argv[i], "-w") == 0){
            words = true;
        }
        else if (strcmp(argv[i], "--bytes") == 0 || strcmp(argv[i], "-c") == 0){
            bytes = true;
        }
        else if (argv[i][0] == '-'){
            std::cout << "invalid command: " << argv[i];
        }
        else{
            filename = argv[i];
        }
    }
    //проверка на отсутствие опций
    if (!(lines || words || bytes) && flag){
        all = true;
    }

    //считывание файла
        std::ifstream file(filename);
        count_lines = 1;
        count_words = 0;
        char prev = ' '; //предыдущий символ

        //проверка на существование файла или корректность пути к нему
        if (!file.is_open()){
            std::cout << "failed to open " << filename << std::endl;
        }
        //проверка на пустой файл
        else if(file.peek() == EOF){
            std::cout << filename << " is empty" << std::endl;
        }

        else{
            file.seekg(0, std::ios::end); //перемещаем курсор из начала файла в конец
            size_file = file.tellg(); //записываем в size_file позицию курсора
            file.seekg(0, std::ios::beg); //возвращаем курсор в начало файла

            //обработка данных файла до тех пор, пока не дойдем до его конца
            while (!file.eof()){
                char ch;
                file.get(ch);
                if (ch == '\n'){
                    count_lines++;
                }
                if (ch != ' ' && (prev == ' ' || prev == '\n')){
                    count_words++;
                }
                prev = ch;
            }

            //вывод параметров
            if (lines || all){
                std::cout << count_lines << ' ';
            }

            if (words || all){
                std::cout << count_words << ' ';
            }

            if(bytes || all){
                std::cout << size_file << ' ';
            }

            std::cout << filename << std::endl;

            average_size_line = (size_file + 9) / lines;
            std::cout << average_size_line;
        }

        file.close();

    return 0;
}

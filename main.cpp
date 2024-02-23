#include "study_in_pink1.h"
#include <vector>

using namespace std;

bool compareFiles(const string &p1, const string &p2)
{
    ifstream f1(p1, ifstream::binary | ifstream::ate);
    ifstream f2(p2, ifstream::binary | ifstream::ate);

    if (f1.fail() || f2.fail())
    {
        return false; // file problem
    }
    //if (f1.tellg() != f2.tellg())
    {
        //return false; // size mismatch
    }
    std::cout << std::endl;
    // seek back to beginning and use std::equal to compare contents
    f1.seekg(0, ifstream::beg);
    f2.seekg(0, ifstream::beg);
    std::cout << f1.rdbuf() << std::endl;
    std::cout << f2.rdbuf() << std::endl;
    std::cout << "-------------------------------------- \n";
    return std::equal(istreambuf_iterator<char>(f1.rdbuf()),
                      istreambuf_iterator<char>(),
                      istreambuf_iterator<char>(f2.rdbuf()));
}

void printFileContent(const std::string& filePath) {
    std::ifstream file(filePath);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    } else {
        std::cout << "Không thể mở tệp tin: " << filePath << std::endl;
    }
}

void readTestcase(const std::string &filename, const char *arr_pwds[], int &num_pwds)
{
    std::ifstream infile(filename);

    if (!infile)
    {
        std::cerr << "Không thể mở file." << std::endl;
        return;
    }

    std::string line;
    num_pwds = 0;
    while (std::getline(infile, line))
    {                                            
        char *pwd = new char[line.length() + 1]; 
        std::strcpy(pwd, line.c_str());          
        arr_pwds[num_pwds++] = pwd;        
    }
}

void sa_tc_01(string input_file, string output_file, int k)
{
    if (k > 0 && k <= 300)
    {

        int HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3;
        if (!readFile(input_file, HP1, HP2, EXP1, EXP2, M1, M2, E1, E2, E3))
        {
            return;
        }
        ofstream outfile(output_file);
        outfile << "----- Mission 1 -----" << endl;
        outfile << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", E1: " << E1 << endl;
        int result = firstMeet(EXP1, EXP2, E1);
        outfile << "EXP1: " << EXP1 << ", EXP2: " << EXP2 << ", result: " << result << endl;

        outfile << "----- Mission 2 -----" << endl;
        outfile << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", E2: " << E2 << endl;
        result = traceLuggage(HP1, EXP1, M1, E2);
        outfile << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", M1: " << M1 << ", result: " << result << endl;

        outfile << "----- Mission 3 -----" << endl;
        outfile << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", HP2: " << HP2 << ", EXP2: " << EXP2 << ", E3: " << E3 << endl;
        result = chaseTaxi(HP1, EXP1, HP2, EXP2, E3);
        outfile << "HP1: " << HP1 << ", EXP1: " << EXP1 << ", HP2: " << HP2 << ", EXP2: " << EXP2 << ", result: " << result << endl;
        outfile.close();
    }
    else if (k > 300 && k <= 400)
    {
        std::ifstream infile(input_file);

        if (!infile)
        {
            std::cerr << "Không thể mở file." << std::endl;
            exit;
        }

        std::string s, email;

        if (std::getline(infile, s) && std::getline(infile, email))
        {
            const char *s_cstr = s.c_str();
            const char *email_cstr = email.c_str();
            int result = checkPassword(s_cstr, email_cstr);

            ofstream outfile(output_file);
            outfile << "S: " << s << endl;
            outfile << "Email: " << email << endl;
            outfile << "Result: " << result << endl;
            outfile.close();
        }
        else
        {
            std::cerr << "Không thể đọc file." << std::endl;
        }
    }
    else if (k > 400 && k <= 500)
    {
        const int MAX_PWDS = 500;
        const char *arr_pwds[MAX_PWDS];
        int num_pwds;

        readTestcase(input_file, arr_pwds, num_pwds); 

        int result = findCorrectPassword(arr_pwds, num_pwds);

        ofstream outfile(output_file);
        outfile << "Result: " << result << endl;
        // cout << result << " ";
        outfile.close();

        for (int i = 0; i < num_pwds; ++i)
        {
            delete[] arr_pwds[i];
        }
    }
}

int main(int argc, const char *argv[])
{
    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    vector<int> diff_files;

    for (int i = start; i <= end; ++i)
    {
        cout << i << " ";
        string input_file = "unittest/input_test/input" + to_string(i) + ".txt";
        string output_file = "unittest/your_result/output" + to_string(i) + ".txt";
        string solution_file = "unittest/output_test/output" + to_string(i) + ".txt";
        sa_tc_01(input_file, output_file, i);
        if (!compareFiles(output_file, solution_file))
        {
            diff_files.push_back(i);
        }
    }

    int percent = 100 - (diff_files.size() * 100) / (end - start + 1);

    if (!diff_files.empty())
    {
        cout << "\n-------------------------------------- \nFiles with differences: ";
        for (int i : diff_files)
        {
            cout << i << " ";
        }
    }
    cout << "\n-------------------------------------- \nResult: Pass " << percent << "%" << endl;

    return 0;
}
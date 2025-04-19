
int main()
{
    std::string test_dir = "tests";

    // For Unix-like systems
    std::string command = "ls " + test_dir;

    FILE *pipe = popen(command.c_str(), "r");
    if (!pipe)
    {
        std::cerr << "Error opening pipe!" << std::endl;
        return 1;
    }

    char buffer[128];
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        std::string filename = buffer;
        // Remove newline character
        filename = filename.substr(0, filename.find('\n'));

        std::string full_path = test_dir + "/" + filename;
        std::ifstream file(full_path);
        std::string text;

        if (file.is_open())
        {
            getline(file, text);
            std::cout << "Input: " << text << std::endl;

            int result = process_string(text);
            if (result == 0)
            {
                std::cout << "Result: Success" << std::endl;
            }
            else
            {
                std::cout << "Result: " << result << std::endl;
            }
            std::cout << "------------------------" << std::endl;
        }
    }

    pclose(pipe);
    return 0;
}


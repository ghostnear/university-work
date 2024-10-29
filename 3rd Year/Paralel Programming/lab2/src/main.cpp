#include "utils.hpp"

int main()
{
    std::vector<int> first = {1, 2}, second = {3, 4};
    pipe_t pipe_d[PIPE_SIZE];

    if (pipe(pipe_d) == -1) {
        perror("Could not create pipe.");
        return 1;
    }

    pid_t producer_pid = fork();
    if (producer_pid == 0) {
        close(pipe_d[PIPE_IN]);
        for (size_t index = 0; index < first.size(); index++) {
            int product = first[index] * second[index];
            write(pipe_d[1], &product, sizeof(int));
        }
        int end = PIPE_TERMINATOR;
        write(pipe_d[PIPE_OUT], &end, sizeof(int));
        close(pipe_d[PIPE_OUT]);
        return 0;
    }

    pid_t consumer_pid = fork();
    if (consumer_pid == 0) {
        close(pipe_d[PIPE_OUT]);
        int product;
        int total = 0;
        while (read(pipe_d[PIPE_IN], &product, sizeof(int)) > 0) {
            if (product == PIPE_TERMINATOR)
                break;
            total += product;
        }
        std::cout << "\nScalar product: " << total << "\n\n";
        close(pipe_d[PIPE_IN]);
        return 0;
    }

    close(pipe_d[PIPE_IN]);
    close(pipe_d[PIPE_OUT]);

    waitpid(producer_pid, NULL, 0);
    waitpid(consumer_pid, NULL, 0);

    return 0;
}

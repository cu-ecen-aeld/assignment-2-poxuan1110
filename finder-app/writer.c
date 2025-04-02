#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    // 開啟 syslog
    openlog("writer", LOG_PID | LOG_CONS, LOG_USER);

    // 檢查參數數量
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Missing arguments. Usage: %s <file_path> <text_string>", argv[0]);
        fprintf(stderr, "Usage: %s <file_path> <text_string>\n", argv[0]);
        closelog();
        return EXIT_FAILURE;
    }

    const char *filepath = argv[1];
    const char *text = argv[2];

    // 嘗試開啟文件進行寫入
    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        syslog(LOG_ERR, "Error: Could not create or write to file %s", filepath);
        perror("Error opening file");
        closelog();
        return EXIT_FAILURE;
    }

    // 寫入內容
    if (fprintf(file, "%s", text) < 0) {
        syslog(LOG_ERR, "Error: Failed to write to file %s", filepath);
        perror("Error writing to file");
        fclose(file);
        closelog();
        return EXIT_FAILURE;
    }

    // 關閉文件
    fclose(file);

    // 記錄成功寫入的訊息
    syslog(LOG_DEBUG, "Writing '%s' to '%s'", text, filepath);

    // 關閉 syslog
    closelog();

    return EXIT_SUCCESS;
}


#include "sm3_utility.h"
int sm3_compute_digest(const char *message,
                       size_t msg_len,
                       unsigned char *md) {
    if (!message || !md) {
        return POINT_IS_EMPTY;
    }
    SM3_CTX ctx;
    if (!sm3_init(&ctx)) {
        return SM3_INIT_FAILED;
    }
    int succ = 1;
    if (!sm3_update(&ctx, message, msg_len)) {
        succ = SM3_UPDATE_FAILED;
        goto DONE;
    }
    if (!sm3_final(md, &ctx)) {
        succ = SM3_FINAL_FAILED;
    }
DONE:
    OPENSSL_cleanse(&ctx, sizeof(ctx));
    return succ;
}
int sm3_compute_digest_from_file(const char *message_file_path, const char *md_file_path) {
    char *message = NULL;
    unsigned char md[32] = { 0 };
    // 读消息
    int len = read_file_content(message_file_path, &message);
    if (len <= 0) {
        return READ_FILE_FAILED;
    }
    int succ = sm3_compute_digest(message, len, md);
    if (succ <= 0) {
        goto DONE;
    }
    if (write_file_content(md_file_path, md, sizeof(md)) <= 0) {
        succ = WRITE_FILE_FAILED;
    }
DONE:
    if (message) {
        free(message);
    }
    return succ;
}
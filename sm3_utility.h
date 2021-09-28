#ifndef SM3_UTILITY_H
#define SM3_UTILITY_H
#include <string.h>
#include <openssl/crypto.h>
#include <openssl/err.h>
#include "crypto/sm3.h"
#include "file_utility.h"
enum SM3_UTILITY_ERROR_CODE {
    SM3_INIT_FAILED      = -1,
    SM3_UPDATE_FAILED    = -2,
    SM3_FINAL_FAILED     = -3,
    POINT_IS_EMPTY       = -4,
    READ_FILE_FAILED     = -5,
    WRITE_FILE_FAILED    = -6,
};
// 使用sm3计算消息摘要
// message:待计算的字符串
// msg_len:消息字节数
// md:输出消息摘要
// 函数返回1则计算成功 返回-1 则计算失败
int sm3_compute_digest(const char *message,
                       size_t msg_len,
                       unsigned char *md);
// 使用sm3计算消息摘要
// message_file_path:待计算的文件绝对路径
// md_file_path:消息摘要文件绝对路径
// 函数返回1则计算成功 返回-1 则计算失败
int sm3_compute_digest_from_file(const char *message_file_path, const char *md_file_path);

#endif
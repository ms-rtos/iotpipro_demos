/*
 * Copyright (c) 2015-2020 ACOINFO Co., Ltd.
 * All rights reserved.
 *
 * Detailed license information can be found in the LICENSE file.
 *
 * File: demo_sdcard.c SDCARD file system operation demo.
 *
 * Author: Yu.kangzhi <yukangzhi@acoinfo.com>
 *
 */

#include <ms_rtos.h>

#define TEST_DIR_PATH       "/sd0/test_dir"
#define TEST_FILE_PATH      "/sd0/test_file"

static ms_uint8_t           read_buf[10];
static ms_uint8_t           write_buf[10] = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

int main (int argc, char **argv)
{
    MS_DIR *dir;
    ms_dirent_t dirent;
    ms_dirent_t *result;
    int fd;
    int ret;

    dir = ms_io_opendir("/sd0");
    if (dir != MS_NULL) {
        /*
         * Create directory TEST_DIR_PATH
         */
        ret = ms_io_access(TEST_DIR_PATH, R_OK);
        if (ret < 0) {
            ms_printf("Directory %s not exist, create it.\n", TEST_DIR_PATH);

            ret = ms_io_mkdir(TEST_DIR_PATH, 0666);
            if (ret < 0) {
                ms_printf("Failed to create %s, errno = %d!\n", TEST_DIR_PATH, errno);
                return  (-1);
            }
        }

        /*
         * Create file TEST_FILE_PATH
         */
        ret = ms_io_access(TEST_FILE_PATH, R_OK);
        if (ret < 0) {
            ms_printf("File %s not exist, create it.\n", TEST_FILE_PATH);

            fd = ms_io_open(TEST_FILE_PATH, O_CREAT | O_RDWR, 0666);
            if (fd < 0) {
                ms_printf("Failed to create %s, errno = %d!\n", TEST_FILE_PATH, errno);
                return  (-1);
            }

        } else {
            fd = ms_io_open(TEST_FILE_PATH, O_RDWR, 0666);
            if (fd < 0) {
                ms_printf("Failed to open %s, errno = %d!\n", TEST_FILE_PATH, errno);
                return  (-1);
            }
        }

        /*
         * Write and read TEST_FILE_PATH
         */
        ret = ms_io_write(fd, write_buf, sizeof(write_buf));
        if (ret != 10) {
            ms_printf("Failed to write file, errno = %d!\n", errno);
            ms_io_close(fd);
            return  (-1);
        }

        ret = ms_io_lseek(fd, 0, SEEK_SET);
        if (ret != 0) {
            ms_printf("Failed to lseek file, errno = %d!\n", errno);
            ms_io_close(fd);
            return  (-1);
        }

        ret = ms_io_read(fd, read_buf, sizeof(read_buf));
        if (ret != 10) {
            ms_printf("Failed to read file, errno = %d!\n", errno);
            ms_io_close(fd);
            return  (-1);
        }

        if (memcmp(write_buf, read_buf, sizeof(read_buf)) != 0) {
            ms_printf("File content compare failed!\n");
            ms_io_close(fd);
            return  (-1);
        }

        ms_io_close(fd);

        /*
         * Remove TEST_FILE_PATH
         */
        ret = ms_io_unlink(TEST_FILE_PATH);
        if (ret < 0) {
            ms_printf("Failed to remove %s, errno = %d!\n", TEST_FILE_PATH, errno);
        }

        ms_printf("List /sd0:\n");
        do {
            ret = ms_io_readdir_r(dir, &dirent, &result);
            if ((ret > 0) && (result != MS_NULL)) {
                if ((strcmp(result->d_name, ".") == 0) || (strcmp(result->d_name, "..") == 0)) {
                    continue;
                }

                ms_printf("%s\n", result->d_name);
            } else {
                break;
            }
        } while (MS_TRUE);

        ms_io_closedir(dir);

    } else {
        ms_printf("Failed to open /sd0, errno = %d!\n", errno);
    }

    return  (0);
}

import os
import ctypes

lib = ctypes.CDLL("libcksum.so")
libc = ctypes.cdll.LoadLibrary("libc.so.6")


def test_cksum(file, opt):
    opt = ctypes.create_string_buffer(bytes(opt, encoding="utf-8"))
    stdin = ctypes.c_void_p.in_dll(libc, "stdin")
    lib.cksum(stdin, opt)


if __name__ == "__main__":
    test_cksum("cksum.c", "--help")
    test_cksum("cksum.c", "--version")
    test_cksum("cksum.c", "stdin")

#!/usr/bin/env python3
"""Decode the hex representation of a CAN status message.

Author: Felix Widmaier <felix.widmaier@tue.mpg.de>
(c) 2022, Max Planck Gesellschaft
License: BSD 3-clause
"""
import argparse
import sys


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("status_msg_hex", metavar="HEX", type=lambda x: int(x, 16))
    args = parser.parse_args()

    code = args.status_msg_hex
    err = code >> 5

    err_msg = {
        0: "No error",
        1: "Encoder error",
        2: "CAN receive timeout",
        3: "Critical motor temperatur",
        4: "Error in Position Converter module.",
        5: "Position rollover",
        6: "INVALID",
        7: "Other error",
    }

    print("Status Message: %#x" % code)
    print("")
    print("System enabled: %d" % bool(code & 1))
    print("Motor 1 enabled: %d" % bool(code & 1 << 1))
    print("Motor 1 ready: %d" % bool(code & 1 << 2))
    print("Motor 2 enabled: %d" % bool(code & 1 << 3))
    print("Motor 2 ready: %d" % bool(code & 1 << 4))
    print("Error: [%d] %s" % (err, err_msg[err]))

    return 0


if __name__ == "__main__":
    sys.exit(main())

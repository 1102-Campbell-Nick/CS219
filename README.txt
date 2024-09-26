Author: Nick Campbell
Date: 9/25/2024

To run this code:
    (1.) In terminal, type "make" and hit enter.
    (2.) After success, type "./machine" to run the code.
    (3.) If there is no error reading the file, it should perform the operator specified in the file on the hex numbers provided.

Process of Code:
    (1.) First, the program will try to open the file, only if it's successful will it continue (It will tell you if it couldnt open file).
    (2.) Next, the program begins a while loop by only doing the loop if it can read from the file.
    (3.) The program then outputs the beginning part of the operation, like the operator and the two values. This is because they are still in string form.
    (4.) After, it will convert the two hex numbers from a string to a uint32_t (unsigned 32 bit integer)
    (5.) Once converted, the program will check what operator was read from the file against if statements until it finds the matching one.
    (6.) Inside the if statements, it will perform the operation identified. For us this is always addition for now.
    (7.) With the answer to the operation, we store it in a value and print it into the already printed equation from earlier. The <iomanip> library allows us to print it in hex.
    (8.) Using the answer value, we check for overflow by comparing one of the input numbers against it. If the answer is smaller, we know an overflow occured. This comparison essentially checks for a carry out.

Answer Explanation:
    (1.) This answer is correct, it translates to 0001 + 0001 which is just 0010, or 0x2. There is no overflow as we are only working with 4 bit addition.
    (2.) This answer is also correct. No matter the order, A + 5 = F. This is true for all hex bits here. There is still no overflow since there was no carry out.
    (3.) This answer is wrong, 0xFFFFFFFF + 0x1 should be 0x100000000. Since we are only allowed 32 bit, though, the 1 in msb got truncated out to 0x0. This means there was an overflow, since there was a carry out.
    (4.) This answer is correct, the number of bits is less than 32 by half so there's no carry out (overflow) chance.
    (5.) This is correct too, it's just a big 32 bit operation. It's contained in it's 32 bit limit, though. We can tell once again because both operands are smaller than the output, showing no carryout/overflow.
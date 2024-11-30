Author: Nick Campbell
Date: 10/29/2024

To run this code:
    (1.) In terminal, type "make" and hit enter.
    (2.) After success, type "./machine" to run the code.
    (3.) If there is no error reading the file, it should perform the commands specified in the file using the hex numbers provided.

Process of Code:
    (1.) First, the program will try to open the file, only if it's successful will it continue (It will tell you if it couldnt open file).
    (2.) Next, the program begins a while loop by only doing the loop if it can read from the file, it also initializes all registers and flags to 0.
    (3.) The program then outputs the operation in machine language format, with the operator in front and the necessary registers after.
    (4.) After, the program will check what operator was read from the file against if statements until it finds the matching one. 
    (5.) Once the operator is found (with or without S at the end), it will find the correct registers based off a converter for the registers array.
    (6.) Next, it will perform the operation identified on those registers using normal operators (+ or -) or binary operations (& or | or ^ or ~) or shifting (<< or >>).
    (7.) With the answer to the operation, we store it in the designated register and print it into the already printed equation from earlier. The <iomanip> library allows us to print it in hex.
    (8.) Last, we check the operator on if it has a last letter of 'S', so we know to update flags. This is done using a variety of methods based off which operator is active, but it wil affect all necessary ones.

Answer Explanation:
    (MOV) -
        For this, we take the needed uint32_t from the register array using the converter and simply set it equal to the number in the file.
    (ADD) - 
        For this, both values are uint32_t, as you need the same data type for addition. This is as simple as using the addition operator on the two registers chosen and putting the answer in the array as well.
    (AND) - 
        This also uses two uint32_t, for the same reason. For this operation, we use the <bitwise> library & operator to simply and them together and put in the correct register.
    (LSR) - 
        This one uses a shift int and a uint32_t, because shifting needs a shift number. Using the <bitwise> ">>" operator, it does a lsr for the int amount of times, shifting in a 0.
    (LSL) - 
        This is very similar to lsr, but instead of <bitwise> ">>" it uses "<<".
    (ORR) - 
        This is almost identical to the and from earlier, using <bitiwse> | instead of the &.
    (SUB) - 
        Once again, this is similar to a previous one, the add. The only difference for it is it uses the regular - operator instead of the +.
    (XOR) - 
        For this, it uses the two uint32_t again. To xor, we use the <bitwise> ^ operator to simply do it.

Flags:
    (N) -
        To preface, the N flag checks the msb, or 31 bit in a 32 bit number, to see if it is a one. The msb can be used as a sign bit by CPU, and a "1" indicates negative while "0" is positive.
        For us, since we are using 32 bit numbers, we can use a <bitwise> & to mask off every bit but the msb to check it. The mask for a 32 bit num in hex is 0x80000000, or 1000 0000 0000 0000 0000 0000 0000 0000.
    (Z) -
        To preface this one, the Z flag simply checks if the result of the operation is 0, thats it.
        For us, the best way to do that is to simply check if the answer is equal to 0.
    (C) -
        To preface the c flag, we should know it is known as the carry flag. It's purpose is to check for a carry in arithmetic operations and the shifted bit in shifting operations.
        To check for this:
            (Addition) - If the answer is smaller than an input register, there is an size overflow and it should be set.
            (Subtraction) - In an equation A = B - C, if B is bigger than C, there won't be any borrowing so the carry flag should be set, if there is borrowing, the carry flag should not be set.
            (Shifting) - This is as simple as checking what bit was shifted out of the number, which is just two equations, one for lsl and one for lsr. If it's "1", carry flag is one, and visa versa.
    (V) -
        To preface the last flag, v, it is only used in the arithmetic operations to indicate signed overflow. This is a completely different type of flag then the c one.
        In any situation, the way to check for this flag is simple, check the msb for sign, similar to the n flag, but instead compare it with the other registers' sign.
        Put simply, if the sign of the two operands, B and C from previous example, are the same, but the answer sign is different, there is a signed overflow. I would like to point out the register simulation says that the subs operation sets the v flag, but according to the definition before, it shouldn't because all msbs are 1, so I must be missing something.

Extra Credit:
    (CMP) -
        This operation is quite simple, it follows subtract very similarly in almost every way. The only difference is it doesn't set any register value and it ALWAYS sets the flags.
        All I did was read it normally and trash the little "<...>" part, then perform subs in a way that doesn't set a register.
    (TST) -
        This operations is also quite simple, except it follows the and operation like cmp follows sub. This has the same differences as cmp.
        I did the same thing as cmp, but tst only affects n and z.
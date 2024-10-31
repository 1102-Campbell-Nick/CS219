Author: Nick Campbell
Date: 10/29/2024

To run this code:
    (1.) In terminal, type "make" and hit enter.
    (2.) After success, type "./machine" to run the code.
    (3.) If there is no error reading the file, it should perform the commands specified in the file using the hex numbers provided.

Process of Code:
    (1.) First, the program will try to open the file, only if it's successful will it continue (It will tell you if it couldnt open file).
    (2.) Next, the program begins a while loop by only doing the loop if it can read from the file.
    (3.) The program then outputs the beginning part of the operation, like the operator and the two (or one for NOT) values. This is because they are still in string form.
    (4.) After, the program will check what operator was read from the file against if statements until it finds the matching one. 
    (5.) Once the operator is found (with or without S at the end), it will convert the two numbers from the strings to whatever numbers the operation needs (uint32_t, int32_t, or int).
    (6.) Next, it will perform the operation identified using normal operators (+ or -) or binary operations (& or | or ^ or ~) or shifting (<< or >>).
    (7.) With the answer to the operation, we store it in a value and print it into the already printed equation from earlier. The <iomanip> library allows us to print it in hex.
    (8.) Last, we check the operator on if it has a last letter of 'S', so we know to update flags. We can do this by anding with 0x80000000 for N and checking if == 0 for Z.

Answer Explanation:
    (ADD) - 
        For this, both values are uint32_t, as you need the same data type for addition. This is as simple as using the addition operator on the two values.
    (AND) - 
        This also uses two uint32_t, for the same reason. For this operation, we use the <bitwise> library & operator to simply and them together.
    (ASR) - 
        This one is different, it uses a int32_t and a int, one for the signed number and one for the shift number. Using the <bitwise> >> operator, and the fact its a uint32_t, it will perform a asr operation.
    (LSR) - 
        This one also uses a shift int, but has a uint32_t instead. Using the same <bitwise> >> operator, it does a lsr instead because its a uint32_t and not a int32_t.
    (LSL) - 
        This is very similar to lsr, but instead of <bitwise> >> it uses <<.
    (NOT) - 
        This is the only operator this time that uses one input, a uint32_t. Using the <bitwise> ~, we can easily not the number.
    (ORR) - 
        This is almost identical to the and from earlier, using <bitiwse> | instead of the &.
    (SUB) - 
        Once again, this is similar to a previous one, the add. The only difference for it is it uses the regular - operator instead of the +.
    (XOR) - 
        For this, it uses the two uint32_t again. To xor, we use the <bitwise> ^ operator to simply do it.

Flags:
    (N) -
        To preface, the N flag checks the msb, or 31 bit in a 32 bit number, to see if it is a one. The msb can be used as a sign bit by CPU, and a one indicated negative while 0 is positive.
        For us, since we are using 32 bit numbers, we can use a <bitwise> & to mask off every bit but the msb to check it. The mask for a 32 bit num in hex is 0x80000000, or 1000 0000 0000 0000 0000 0000 0000 0000.
    (Z) -
        To preface this one, the Z flag simply checks if the result of the operation is 0, thats it.
        For us, the best way to do that is to simply check if the answer is equal to 0.
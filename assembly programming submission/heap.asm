extern init_v
extern pop_v
extern push_v
extern size_v
extern get_element_v
extern resize_v
extern delete_v
section .text
global init_h
global delete_h
global size_h
global insert_h
global get_max
global pop_max
global heapify
global heapsort

init_h:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13 
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        push rdi
         push rsi
         
         mov rdi , 24
         pain:
         extern malloc ; allocation of a vector data type
         call malloc
         madara:
         pop rsi
         pop rdi

         ; a struct vector data type is stored in rax

         push rdi
         mov rdi, rax
         itachi:
         call init_v ; initialising the vactor data type
         mov r15 , rdi
         konan:
         pop rdi

         ; rdi is again the heap struct but r15 contain a vector data type that is initialised
         mov r14 , [r15] 
         mov r13 , [r15+8]
         mov r12 , [r15+16]
         mov [rdi] , r14
         mov [rdi+8] , r13
         mov [rdi+16] , r12
         ; initialization done

        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret

delete_h:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        mov r9 , rdi ; r9 is of type vector not vector*
        push rdi
        mov rdi , r9 ; just supply the arr for deletion
        call delete_v
        pop rdi

        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret


size_h:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        mov r9 , rdi
        push rdi
        mov rdi , r9 ; just provide the pointer to the array
        call size_v
        pop rdi
        ; now the rax holds the size

        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret


insert_h:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        mov r9 , rdi
        mov r10 , rsi ; r10 contain the insert value
        
        ; FIRST INSERT THE INPUT ELEMENT AT THE LAST INDEX
        push rdi
        push rsi

        mov rdi , r9
        mov rsi , r10
        call push_v
        
        pop rsi
        pop rdi
        ; THEN USE THE CONCEPT OF ADDING ELEMENT TO A HEAP , i.e REPLACE PARENT BY CHILD AS LONG AS CHILD GREATER THAN PARENT
        mov r11 , QWORD[rdi+8]
        sub r11 , 1
        mov r12 , 0
        while12:
        cmp r12 , r11 ; t = r11
        jge goto
        mov r13 , r11
        mov r14 , r11
        sub r14 , 1
        shr r14 , 1
        imul r13 , 8
        imul r14 , 8

        add r13 , QWORD[rdi+16] ; store[t]
        add r14 , QWORD[rdi+16] ; store[par[t]]

        mov r15 , QWORD[r13] ; store[t]
        mov rbx , QWORD[r14] ; store[par[t]]

        cmp rbx, r15
        jge goto
        
        mov QWORD[r13] , rbx
        mov QWORD[r14] , r15 ; swap done

        sub r11 , 1
        shr r11 , 1
        jmp while12

        goto:




        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret

get_max:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        ; mov r8 , rdi
        ; mov r9 , QWORD[rdi]
        ; mov r10 , QWORD[rdi+8]
        ; mov r11 , QWORD[rdi+16]
        ; mov rdx,0
        ; mov rbx,0
        ; loopez:
        ; cmp rbx , r10
        ; jge ending
        ; mov r14 , rbx
        ; imul r14 , 8
        ; add r14 , r11
        ; loopez2:
        ; cmp rdx,[r14]
        ; jge ending2
        ; mov rdx , [r14]
        ; ending2:
        ; add rbx , 1
        ; jmp loopez

        ; ending:
        ; mov rax , rdx
        
        ;just return the top element 
        mov r8 , QWORD[rdi+16]
        misato_evangelion:
        mov rax , [r8]

        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret
 
pop_max:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        ; FIRST SWAP THE FIRST AND LAST ELEMENT THEN CALL HEAPIFY FUNCTION ON SIZE-1 , POP OUT THE LAST ELEMENT 
        mov rax , QWORD[rdi+16]
        mov r8 , 0
        imul r8 , 8
        add rax , r8
        mov rax , [rax]
        
        mov r8 , QWORD[rdi+8]
        sub r8 , 1
        mov r9 , 0

        imul r8 , 8
        imul r9 , 8
        add r8 , QWORD[rdi+16]
        add r9 , QWORD[rdi+16]

        mov r14 , QWORD[r8]
        mov r15 , QWORD[r9]
        
        mov QWORD[r8] , r15
        mov QWORD[r9] , r14

        push rdi
        push rsi
        push rdx

        mov rsi , QWORD[rdi+8]
        sub rsi , 1
        mov rdx , 0

        call heapify

        pop rdx
        pop rsi
        pop rdi

        push rdi
        call pop_v
        pop rdi


        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret

heapify:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        ; rdi contains the vector
        mov r9 , rsi; size
        mov r11 , rdx ; index
        
        mov r15 , 0
        cmp r9 , r15
        je function_over
        mov r13 , r11 ; r13 is largest
        
        mov r14 , r11
        imul r14 , 2
        add r14 , 1 ; r14 is left

        mov r15 , r11
        imul r15 , 2
        add r15 , 2 ; r15 is right

        check1:
        cmp r14 , r9
        jge check3
        check2:
        mov r8 , r14
        mov r10 , r13
        imul r8 , 8
        imul r10 , 8
        add r8 , QWORD[rdi+16]
        add r10 , QWORD[rdi+16]
        mov r8 , QWORD[r8]
        mov r10 , QWORD[r10]
        cmp r10 , r8 ; if(a[large] < a[left])
        jge check3
        mov r13 , r14


        check3:
        cmp r15 , r9
        jge further
        check4:
        mov r8 , r15
        mov r10 , r13
        imul r8 , 8
        imul r10 , 8
        add r8 , QWORD[rdi+16]
        add r10 , QWORD[rdi+16]
         mov r8 , QWORD[r8]
        mov r10 , QWORD[r10]
        cmp r10 , r8 ; if(a[large] < a[right])
        jge further
        mov r13 , r15

        further:
        cmp r13 , r11
        je function_over
        mov r8 , r13
        mov r10 , r11
        imul r8 , 8
        imul r10 , 8
        add r8 , QWORD[rdi+16]
        add r10 , QWORD[rdi+16]
        mov rbx , QWORD[r8]
        mov rcx , QWORD[r10]
        mov QWORD[r8] , rcx
        mov QWORD[r10] , rbx
         
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        mov rsi , r9
        mov rdx , r13
        call heapify
        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx


        function_over:
        

        
        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret

heapsort:
        push rbp
        mov rbp, rsp
        push rax
        push rbx
        push rcx
        push rdx
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE
        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rdx
        pop rcx
        pop rbx
        mov rsp, rbp
        pop rbp
        ret


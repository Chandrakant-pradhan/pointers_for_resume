extern realloc
extern free


section .text
global init_v
global delete_v
global resize_v
global get_element_v
global push_v
global pop_v
global size_v

;init working fine
;delete working fine
;get element working fine
;push working fine
; pop and size working fine 
;resize not working correctly
init_v:
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
         mov QWORD[rdi], 10 ; initialising with some space
    
         mov QWORD[rdi+8], 0 ; size = 0
         b:
         ;xor rax, rax
         push rdi
         push rsi
         
         mov rdi , 80 ; then malloc to allocate the required space
         extern malloc
         call malloc
         pop rsi
         pop rdi
         c:
         mov QWORD[rdi+16], rax  ; move the pointer of the allocated array to the ptr
         d:

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

delete_v:
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
        mov rax, QWORD[rdi+16]  
        e:
       test rax, rax ; checks if rax is null
       f:
       jz leave
       
       push rdi
       g:
       mov  rdi, rax        ;address pushed in rax   
       h:
       call free               ; freed
       i:
       pop rdi
        j:
       leave:
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

resize_v:
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
        mov r8 , QWORD[rdi] ; buff size
        k:
        mov r9 , QWORD[rdi+8] ; size
        l:
        mov r10 , QWORD[rdi+16] ; base address
        m:

        mov r11 , rsi ; should be in format (number of ele needed)
        mov r12 , rsi ; buffer size needed
        imul r11 , 8
        n:
        
        push rdi
        push rsi
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        mov rdi , r11
        kappa:
        extern malloc ; allocationa new array with bigger size
        call malloc
        mappa:
        pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rsi
        pop rdi
         ; LOOPING THROUGH THE ORIGINAL ARRAY
         ; BASICALLY COPYING THE ORIGINAL ARRAY TO THE BIGGER ARRAY
        ; now eax stores the array of size 2*buffer size
        mov rbx , 0
        for:
        hit:
        cmp rbx , r12 
        jge over
        mov r13 , rbx
        mov r14 , rbx
        imul r13 , 8
        imul r14 , 8
        add r13 , r10 ; arr[i] of the real array 
        add r14 , rax; the malloced array
        
        mov r15 , QWORD[r13]
        mov QWORD[r14] , r15
        ; so mallo[i] = arr[i]

        inc rbx; i++
        jmp for
        

        over:
        ;Once over just free up the original array and assign it a new pointer
         mov r15 , [rdi+16]
         mov [rdi+16] , eax
         mov [rdi] , r12
         push rdi
         mov  rdi, r15          ; Address needed in rdi (mov %rax, %rdi).
         call free               ; And free it.
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

get_element_v:
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
        ; just return the address
        mov r8 , QWORD[rdi+16] ; r8 has the address base
        mov r9 , rsi ; r9 has the index
        mov r10 , r9
        imul r10 , 8
        add r10 , r8 ; this is the address of the arr[i]

        mov rax , r10 ; you need to return the address not the value

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

push_v:
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
        ; input in rdi and rsi
        mov r8 , QWORD[rdi] ; r8 stores the buffer size
        w:
        mov r9 , QWORD[rdi+8]; r9 stores the size of the arrar
        x:
        mov r10 , QWORD[rdi+16] ; r10 stores the pointer to the array
        y:
        mov r11 , rsi ; r11 has the input value
        z:
        cmp r9 , r8
        ab:
        je loop_hole
        ; if they are not equal then  that means ki size < buff_size
        mov r12 , r9
        bc:
        imul r12 , 8
        cd:
        add r12 , r10  
        de:
        ; r12 holds the arr[size()]
        mov QWORD[r12] , r11
        ef:
        mov r15 , r9
        fg:
        add r15 , 1
        mov QWORD[rdi+8] , r15
        ;size++
        gh:
        jmp exit
        ;THIS IS THE CASE WHEN ARRAY IS FULL 
       loop_hole:
        hi:
        push rdi
        push rsi
        push r8
        push r9
        push r10
        push r11
        push r12
        push r13
        push r14
        push r15
        
        imul r8 , 2 ; first the buff size = 2* old_buff
        mov rsi , r8
        ij:
        call resize_v

        
         pop r15
        pop r14
        pop r13
        pop r12
        pop r11
        pop r10
        pop r9
        pop r8
        pop rsi
        pop rdi

        mov r8 , QWORD[rdi] ; r8 stores the buffer size
        mov r9 , QWORD[rdi+8]; r9 stores the size of the arrar
        mov r10 , QWORD[rdi+16] ; r10 stores the pointer to the array
        mov r11 , rsi ; r11 has the input value

         mov r12 , r9
        imul r12 , 8
        add r12 , r10  
        ; r12 holds the arr[size()]
        naruto:
        mov QWORD[r12] , r11
        mov r15 , r9
        add r15 , 1
        mov QWORD[rdi+8] , r15
        ;size++


         
        exit:
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

pop_v:
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
         mov r8 , QWORD[rdi+16]
        mov r9 , QWORD[rdi+8]
        mov r10 , r9
        
        sub r9 , 1
        push rdi
        push rsi
        mov rsi , r9
        call get_element_v
        pop rsi
        pop rdi
        mov r15 , QWORD[rax]
        mov rax , r15
        sub r10 , 1
        mov QWORD[rdi+8] , r10



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

size_v:
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
        ;return value is stored in rax
        ; ENTER YOUR CODE HERE, DO NOT MODIFY EXTERNAL CODE

        mov rax , QWORD[rdi+8]


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


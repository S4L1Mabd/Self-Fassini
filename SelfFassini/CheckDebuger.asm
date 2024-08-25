.code 

getPEB proc
    mov rax, gs:[60h]  ;PEB
    ret
getPEB endp

checkforDebug proc
   xor eax,eax
   call getPEB
   movzx eax, byte ptr [rax+2h]   ;PEB eax <---- BiengDebugged of PEB 
   ret 
checkforDebug endp 
end
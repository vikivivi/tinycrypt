; Listing generated by Microsoft (R) Optimizing Compiler Version 16.00.40219.01 

	TITLE	C:\hub\lightmac\ref\c\src\lightmac.c
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB LIBCMT
INCLUDELIB OLDNAMES

PUBLIC	_encodeCounter
; Function compile flags: /Ogspy
;	COMDAT _encodeCounter
_TEXT	SEGMENT
_counter$ = 8						; size = 8
_output$ = 16						; size = 4
_encodeCounter PROC					; COMDAT
; File c:\hub\lightmac\ref\c\src\lightmac.c
; Line 12
	mov	eax, DWORD PTR _counter$[esp-4]
	push	3
	pop	ecx
$LL3@encodeCoun:
; Line 13
	mov	edx, DWORD PTR _output$[esp-4]
	mov	BYTE PTR [ecx+edx], al
; Line 14
	mov	edx, DWORD PTR _counter$[esp]
	shrd	eax, edx, 8
	shr	edx, 8
	dec	ecx
	mov	DWORD PTR _counter$[esp], edx
	jns	SHORT $LL3@encodeCoun
; Line 16
	ret	0
_encodeCounter ENDP
_TEXT	ENDS
PUBLIC	_tag
EXTRN	_BCEncrypt:PROC
EXTRN	_memset:PROC
; Function compile flags: /Ogspy
;	COMDAT _tag
_TEXT	SEGMENT
_blockOutput$ = -32					; size = 8
_counter$ = -24						; size = 8
_value$ = -16						; size = 8
_blockInput$ = -8					; size = 8
_message$ = 8						; size = 4
_messageLength$ = 12					; size = 8
_output$ = 20						; size = 4
_key$ = 24						; size = 4
_tag	PROC						; COMDAT
; Line 18
	push	ebp
	mov	ebp, esp
	sub	esp, 32					; 00000020H
; Line 32
	and	DWORD PTR _counter$[ebp+4], 0
	push	ebx
	push	esi
	push	edi
	xor	eax, eax
	lea	edi, DWORD PTR _value$[ebp]
	xor	ebx, ebx
	stosd
	inc	ebx
; Line 36
	cmp	DWORD PTR _messageLength$[ebp+4], 0
	stosd
	ja	SHORT $LL20@tag
	mov	edi, DWORD PTR _messageLength$[ebp]
	cmp	edi, 4
	jb	SHORT $LN43@tag
$LL20@tag:
; Line 38
	lea	eax, DWORD PTR _blockInput$[ebp]
	push	eax
	push	DWORD PTR _counter$[ebp+4]
	push	ebx
	call	_encodeCounter
; Line 46
	push	DWORD PTR _key$[ebp]
	mov	esi, DWORD PTR _message$[ebp]
	lea	eax, DWORD PTR _blockOutput$[ebp]
	push	eax
	lea	eax, DWORD PTR _blockInput$[ebp]
	lea	edi, DWORD PTR _blockInput$[ebp+4]
	push	eax
	movsd
	call	_BCEncrypt
	add	esp, 24					; 00000018H
; Line 50
	xor	eax, eax
$LL15@tag:
; Line 51
	mov	cl, BYTE PTR _blockOutput$[ebp+eax]
	xor	BYTE PTR _value$[ebp+eax], cl
	inc	eax
	cmp	eax, 8
	jb	SHORT $LL15@tag
; Line 53
	add	DWORD PTR _messageLength$[ebp], -4	; fffffffcH
	adc	DWORD PTR _messageLength$[ebp+4], -1
; Line 54
	add	DWORD PTR _message$[ebp], 4
; Line 55
	add	ebx, 1
	adc	DWORD PTR _counter$[ebp+4], 0
	cmp	DWORD PTR _messageLength$[ebp+4], 0
	ja	SHORT $LL20@tag
; Line 36
	jb	SHORT $LN52@tag
	cmp	DWORD PTR _messageLength$[ebp], 4
	jae	SHORT $LL20@tag
$LN52@tag:
	mov	edi, DWORD PTR _messageLength$[ebp]
$LN43@tag:
; Line 60
	xor	ecx, ecx
	cmp	DWORD PTR _messageLength$[ebp+4], ecx
	jb	SHORT $LN53@tag
	ja	SHORT $LN44@tag
	cmp	edi, ecx
	jbe	SHORT $LN53@tag
$LN44@tag:
	mov	esi, DWORD PTR _message$[ebp]
	lea	eax, DWORD PTR _blockInput$[ebp]
	sub	esi, eax
$LL12@tag:
; Line 61
	lea	eax, DWORD PTR _blockInput$[ebp+ecx]
	mov	dl, BYTE PTR [esi+eax]
	mov	BYTE PTR [eax], dl
	xor	eax, eax
	inc	ecx
	cmp	eax, DWORD PTR _messageLength$[ebp+4]
	jb	SHORT $LL12@tag
; Line 60
	ja	SHORT $LN53@tag
	cmp	ecx, edi
	jb	SHORT $LL12@tag
$LN53@tag:
; Line 67
	lea	eax, DWORD PTR [edi+1]
	mov	BYTE PTR _blockInput$[ebp+edi], 128	; 00000080H
	cmp	eax, 8
	jae	SHORT $LN54@tag
; Line 64
	push	8
	pop	edx
	sub	edx, eax
	push	edx
	lea	ecx, DWORD PTR _blockInput$[ebp+eax]
	push	0
	push	ecx
	call	_memset
	add	esp, 12					; 0000000cH
$LN54@tag:
; Line 73
	xor	eax, eax
$LL6@tag:
; Line 74
	mov	cl, BYTE PTR _blockInput$[ebp+eax]
	xor	BYTE PTR _value$[ebp+eax], cl
	inc	eax
	cmp	eax, 8
	jb	SHORT $LL6@tag
; Line 78
	mov	eax, DWORD PTR _key$[ebp]
	add	eax, 16					; 00000010H
; Line 79
	push	eax
	lea	eax, DWORD PTR _blockOutput$[ebp]
	push	eax
	lea	eax, DWORD PTR _value$[ebp]
	push	eax
	call	_BCEncrypt
; Line 83
	mov	edi, DWORD PTR _output$[ebp]
	lea	esi, DWORD PTR _blockOutput$[ebp]
	movsd
	add	esp, 12					; 0000000cH
	movsd
	pop	edi
	pop	esi
	pop	ebx
; Line 85
	leave
	ret	0
_tag	ENDP
_TEXT	ENDS
PUBLIC	_verify
; Function compile flags: /Ogspy
;	COMDAT _verify
_TEXT	SEGMENT
_tempTag$ = -8						; size = 8
_message$ = 8						; size = 4
_messageLength$ = 12					; size = 8
_candidateTag$ = 20					; size = 4
_key$ = 24						; size = 4
_verify	PROC						; COMDAT
; Line 91
	push	ebp
	mov	ebp, esp
	push	ecx
	push	ecx
	push	esi
; Line 96
	push	DWORD PTR _key$[ebp]
	lea	eax, DWORD PTR _tempTag$[ebp]
	push	eax
	push	DWORD PTR _messageLength$[ebp+4]
	push	DWORD PTR _messageLength$[ebp]
	push	DWORD PTR _message$[ebp]
	call	_tag
; Line 100
	mov	ecx, DWORD PTR _candidateTag$[ebp]
	lea	eax, DWORD PTR _tempTag$[ebp]
	add	esp, 20					; 00000014H
	xor	esi, esi
	sub	ecx, eax
$LL4@verify:
; Line 101
	lea	eax, DWORD PTR _tempTag$[ebp+esi]
	mov	dl, BYTE PTR [ecx+eax]
	cmp	dl, BYTE PTR [eax]
	jne	SHORT $LN8@verify
; Line 100
	inc	esi
	cmp	esi, 8
	jl	SHORT $LL4@verify
; Line 105
	xor	eax, eax
	inc	eax
$LN5@verify:
	pop	esi
; Line 106
	leave
	ret	0
$LN8@verify:
; Line 102
	xor	eax, eax
	jmp	SHORT $LN5@verify
_verify	ENDP
_TEXT	ENDS
END

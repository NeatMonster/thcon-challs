
challenge.elf:     file format elf32-littlemips


Disassembly of section .text:

00000000 <_start>:
   0:	27bdffe8 	addiu	sp,sp,-24
   4:	afbf0014 	sw	ra,20(sp)
   8:	afbe0010 	sw	s8,16(sp)
   c:	03a0f025 	move	s8,sp
  10:	0c000010 	jal	40 <main>
  14:	00000000 	nop
  18:	00402025 	move	a0,v0
  1c:	0c00018a 	jal	628 <exit>
  20:	00000000 	nop
  24:	00000000 	nop
  28:	03c0e825 	move	sp,s8
  2c:	8fbf0014 	lw	ra,20(sp)
  30:	8fbe0010 	lw	s8,16(sp)
  34:	27bd0018 	addiu	sp,sp,24
  38:	03e00008 	jr	ra
  3c:	00000000 	nop

00000040 <main>:
  40:	27bdff78 	addiu	sp,sp,-136
  44:	afbf0084 	sw	ra,132(sp)
  48:	afbe0080 	sw	s8,128(sp)
  4c:	afb7007c 	sw	s7,124(sp)
  50:	afb60078 	sw	s6,120(sp)
  54:	afb50074 	sw	s5,116(sp)
  58:	afb40070 	sw	s4,112(sp)
  5c:	afb3006c 	sw	s3,108(sp)
  60:	afb20068 	sw	s2,104(sp)
  64:	afb10064 	sw	s1,100(sp)
  68:	afb00060 	sw	s0,96(sp)
  6c:	03a0f025 	move	s8,sp
  70:	afc00014 	sw	zero,20(s8)
  74:	afc00038 	sw	zero,56(s8)
  78:	afc0003c 	sw	zero,60(s8)
  7c:	24060024 	li	a2,36
  80:	3c020000 	lui	v0,0x0
  84:	2445078c 	addiu	a1,v0,1932
  88:	24040001 	li	a0,1
  8c:	0c0001ac 	jal	6b0 <write>
  90:	00000000 	nop
  94:	27c20028 	addiu	v0,s8,40
  98:	24060010 	li	a2,16
  9c:	00402825 	move	a1,v0
  a0:	00002025 	move	a0,zero
  a4:	0c000198 	jal	660 <read>
  a8:	00000000 	nop
  ac:	afc2001c 	sw	v0,28(s8)
  b0:	8fc3001c 	lw	v1,28(s8)
  b4:	24020010 	li	v0,16
  b8:	14620111 	bne	v1,v0,500 <main+0x4c0>
  bc:	00000000 	nop
  c0:	afc00010 	sw	zero,16(s8)
  c4:	1000004a 	b	1f0 <main+0x1b0>
  c8:	00000000 	nop
  cc:	2403000f 	li	v1,15
  d0:	8fc20010 	lw	v0,16(s8)
  d4:	00000000 	nop
  d8:	00621023 	subu	v0,v1,v0
  dc:	27c30010 	addiu	v1,s8,16
  e0:	00621021 	addu	v0,v1,v0
  e4:	90420018 	lbu	v0,24(v0)
  e8:	00000000 	nop
  ec:	a3c20018 	sb	v0,24(s8)
  f0:	93c20018 	lbu	v0,24(s8)
  f4:	00000000 	nop
  f8:	2c420030 	sltiu	v0,v0,48
  fc:	1440000c 	bnez	v0,130 <main+0xf0>
 100:	00000000 	nop
 104:	93c20018 	lbu	v0,24(s8)
 108:	00000000 	nop
 10c:	2c42003a 	sltiu	v0,v0,58
 110:	10400007 	beqz	v0,130 <main+0xf0>
 114:	00000000 	nop
 118:	93c20018 	lbu	v0,24(s8)
 11c:	00000000 	nop
 120:	2442ffd0 	addiu	v0,v0,-48
 124:	a3c20018 	sb	v0,24(s8)
 128:	1000000f 	b	168 <main+0x128>
 12c:	00000000 	nop
 130:	93c20018 	lbu	v0,24(s8)
 134:	00000000 	nop
 138:	2c420041 	sltiu	v0,v0,65
 13c:	144000f1 	bnez	v0,504 <main+0x4c4>
 140:	00000000 	nop
 144:	93c20018 	lbu	v0,24(s8)
 148:	00000000 	nop
 14c:	2c420047 	sltiu	v0,v0,71
 150:	104000ec 	beqz	v0,504 <main+0x4c4>
 154:	00000000 	nop
 158:	93c20018 	lbu	v0,24(s8)
 15c:	00000000 	nop
 160:	2442ffc9 	addiu	v0,v0,-55
 164:	a3c20018 	sb	v0,24(s8)
 168:	8fc20010 	lw	v0,16(s8)
 16c:	00000000 	nop
 170:	30420001 	andi	v0,v0,0x1
 174:	10400005 	beqz	v0,18c <main+0x14c>
 178:	00000000 	nop
 17c:	93c20018 	lbu	v0,24(s8)
 180:	00000000 	nop
 184:	00021100 	sll	v0,v0,0x4
 188:	a3c20018 	sb	v0,24(s8)
 18c:	8fc20014 	lw	v0,20(s8)
 190:	27c30010 	addiu	v1,s8,16
 194:	00621021 	addu	v0,v1,v0
 198:	90430028 	lbu	v1,40(v0)
 19c:	93c20018 	lbu	v0,24(s8)
 1a0:	00000000 	nop
 1a4:	00621025 	or	v0,v1,v0
 1a8:	304300ff 	andi	v1,v0,0xff
 1ac:	8fc20014 	lw	v0,20(s8)
 1b0:	27c40010 	addiu	a0,s8,16
 1b4:	00821021 	addu	v0,a0,v0
 1b8:	a0430028 	sb	v1,40(v0)
 1bc:	8fc20010 	lw	v0,16(s8)
 1c0:	00000000 	nop
 1c4:	30420001 	andi	v0,v0,0x1
 1c8:	10400005 	beqz	v0,1e0 <main+0x1a0>
 1cc:	00000000 	nop
 1d0:	8fc20014 	lw	v0,20(s8)
 1d4:	00000000 	nop
 1d8:	24420001 	addiu	v0,v0,1
 1dc:	afc20014 	sw	v0,20(s8)
 1e0:	8fc20010 	lw	v0,16(s8)
 1e4:	00000000 	nop
 1e8:	24420001 	addiu	v0,v0,1
 1ec:	afc20010 	sw	v0,16(s8)
 1f0:	8fc20010 	lw	v0,16(s8)
 1f4:	00000000 	nop
 1f8:	28420010 	slti	v0,v0,16
 1fc:	1440ffb3 	bnez	v0,cc <main+0x8c>
 200:	00000000 	nop
 204:	24060020 	li	a2,32
 208:	3c020000 	lui	v0,0x0
 20c:	244507b4 	addiu	a1,v0,1972
 210:	24040001 	li	a0,1
 214:	0c0001ac 	jal	6b0 <write>
 218:	00000000 	nop
 21c:	afc00010 	sw	zero,16(s8)
 220:	10000083 	b	430 <main+0x3f0>
 224:	00000000 	nop
 228:	a3c00018 	sb	zero,24(s8)
 22c:	afc00014 	sw	zero,20(s8)
 230:	10000066 	b	3cc <main+0x38c>
 234:	00000000 	nop
 238:	27c20038 	addiu	v0,s8,56
 23c:	8c430004 	lw	v1,4(v0)
 240:	8c420000 	lw	v0,0(v0)
 244:	00000000 	nop
 248:	30420001 	andi	v0,v0,0x1
 24c:	afc20020 	sw	v0,32(s8)
 250:	27c20038 	addiu	v0,s8,56
 254:	8c430004 	lw	v1,4(v0)
 258:	8c420000 	lw	v0,0(v0)
 25c:	0003b6c2 	srl	s6,v1,0x1b
 260:	0000b825 	move	s7,zero
 264:	02c01025 	move	v0,s6
 268:	30430001 	andi	v1,v0,0x1
 26c:	8fc20020 	lw	v0,32(s8)
 270:	00000000 	nop
 274:	00621026 	xor	v0,v1,v0
 278:	afc20020 	sw	v0,32(s8)
 27c:	27c20038 	addiu	v0,s8,56
 280:	8c430004 	lw	v1,4(v0)
 284:	8c420000 	lw	v0,0(v0)
 288:	00031702 	srl	v0,v1,0x1c
 28c:	afc20040 	sw	v0,64(s8)
 290:	afc00044 	sw	zero,68(s8)
 294:	8fc20040 	lw	v0,64(s8)
 298:	00000000 	nop
 29c:	30430001 	andi	v1,v0,0x1
 2a0:	8fc20020 	lw	v0,32(s8)
 2a4:	00000000 	nop
 2a8:	00621026 	xor	v0,v1,v0
 2ac:	afc20020 	sw	v0,32(s8)
 2b0:	27c20038 	addiu	v0,s8,56
 2b4:	8c430004 	lw	v1,4(v0)
 2b8:	8c420000 	lw	v0,0(v0)
 2bc:	00031782 	srl	v0,v1,0x1e
 2c0:	afc20048 	sw	v0,72(s8)
 2c4:	afc0004c 	sw	zero,76(s8)
 2c8:	8fc20048 	lw	v0,72(s8)
 2cc:	00000000 	nop
 2d0:	30430001 	andi	v1,v0,0x1
 2d4:	8fc20020 	lw	v0,32(s8)
 2d8:	00000000 	nop
 2dc:	00621026 	xor	v0,v1,v0
 2e0:	afc20020 	sw	v0,32(s8)
 2e4:	27c20038 	addiu	v0,s8,56
 2e8:	8c430004 	lw	v1,4(v0)
 2ec:	8c420000 	lw	v0,0(v0)
 2f0:	000317c2 	srl	v0,v1,0x1f
 2f4:	afc20050 	sw	v0,80(s8)
 2f8:	afc00054 	sw	zero,84(s8)
 2fc:	8fc30050 	lw	v1,80(s8)
 300:	8fc20020 	lw	v0,32(s8)
 304:	00000000 	nop
 308:	00621026 	xor	v0,v1,v0
 30c:	afc20020 	sw	v0,32(s8)
 310:	27c40038 	addiu	a0,s8,56
 314:	27c20038 	addiu	v0,s8,56
 318:	8c430004 	lw	v1,4(v0)
 31c:	8c420000 	lw	v0,0(v0)
 320:	00032fc0 	sll	a1,v1,0x1f
 324:	00028042 	srl	s0,v0,0x1
 328:	00b08025 	or	s0,a1,s0
 32c:	00038842 	srl	s1,v1,0x1
 330:	ac900000 	sw	s0,0(a0)
 334:	ac910004 	sw	s1,4(a0)
 338:	27c50038 	addiu	a1,s8,56
 33c:	27c20038 	addiu	v0,s8,56
 340:	8c430004 	lw	v1,4(v0)
 344:	8c420000 	lw	v0,0(v0)
 348:	8fc40020 	lw	a0,32(s8)
 34c:	00000000 	nop
 350:	afc40058 	sw	a0,88(s8)
 354:	000427c3 	sra	a0,a0,0x1f
 358:	afc4005c 	sw	a0,92(s8)
 35c:	8fc40058 	lw	a0,88(s8)
 360:	00000000 	nop
 364:	00049fc0 	sll	s3,a0,0x1f
 368:	00009025 	move	s2,zero
 36c:	0052a025 	or	s4,v0,s2
 370:	0073a825 	or	s5,v1,s3
 374:	acb40000 	sw	s4,0(a1)
 378:	acb50004 	sw	s5,4(a1)
 37c:	8fc20020 	lw	v0,32(s8)
 380:	00000000 	nop
 384:	00021600 	sll	v0,v0,0x18
 388:	00021603 	sra	v0,v0,0x18
 38c:	00401825 	move	v1,v0
 390:	8fc20014 	lw	v0,20(s8)
 394:	00000000 	nop
 398:	00431004 	sllv	v0,v1,v0
 39c:	00021e00 	sll	v1,v0,0x18
 3a0:	00031e03 	sra	v1,v1,0x18
 3a4:	83c20018 	lb	v0,24(s8)
 3a8:	00000000 	nop
 3ac:	00621025 	or	v0,v1,v0
 3b0:	00021600 	sll	v0,v0,0x18
 3b4:	00021603 	sra	v0,v0,0x18
 3b8:	a3c20018 	sb	v0,24(s8)
 3bc:	8fc20014 	lw	v0,20(s8)
 3c0:	00000000 	nop
 3c4:	24420001 	addiu	v0,v0,1
 3c8:	afc20014 	sw	v0,20(s8)
 3cc:	8fc20014 	lw	v0,20(s8)
 3d0:	00000000 	nop
 3d4:	28420008 	slti	v0,v0,8
 3d8:	1440ff97 	bnez	v0,238 <main+0x1f8>
 3dc:	00000000 	nop
 3e0:	3c020000 	lui	v0,0x0
 3e4:	24430850 	addiu	v1,v0,2128
 3e8:	8fc20010 	lw	v0,16(s8)
 3ec:	00000000 	nop
 3f0:	00621021 	addu	v0,v1,v0
 3f4:	90430000 	lbu	v1,0(v0)
 3f8:	93c20018 	lbu	v0,24(s8)
 3fc:	00000000 	nop
 400:	00621026 	xor	v0,v1,v0
 404:	304300ff 	andi	v1,v0,0xff
 408:	3c020000 	lui	v0,0x0
 40c:	24440850 	addiu	a0,v0,2128
 410:	8fc20010 	lw	v0,16(s8)
 414:	00000000 	nop
 418:	00821021 	addu	v0,a0,v0
 41c:	a0430000 	sb	v1,0(v0)
 420:	8fc20010 	lw	v0,16(s8)
 424:	00000000 	nop
 428:	24420001 	addiu	v0,v0,1
 42c:	afc20010 	sw	v0,16(s8)
 430:	8fc20010 	lw	v0,16(s8)
 434:	00000000 	nop
 438:	28422001 	slti	v0,v0,8193
 43c:	1440ff7a 	bnez	v0,228 <main+0x1e8>
 440:	00000000 	nop
 444:	24021ff9 	li	v0,8185
 448:	afc20010 	sw	v0,16(s8)
 44c:	1000000e 	b	488 <main+0x448>
 450:	00000000 	nop
 454:	3c020000 	lui	v0,0x0
 458:	24430850 	addiu	v1,v0,2128
 45c:	8fc20010 	lw	v0,16(s8)
 460:	00000000 	nop
 464:	00621021 	addu	v0,v1,v0
 468:	90420000 	lbu	v0,0(v0)
 46c:	00000000 	nop
 470:	1440002d 	bnez	v0,528 <main+0x4e8>
 474:	00000000 	nop
 478:	8fc20010 	lw	v0,16(s8)
 47c:	00000000 	nop
 480:	24420001 	addiu	v0,v0,1
 484:	afc20010 	sw	v0,16(s8)
 488:	8fc20010 	lw	v0,16(s8)
 48c:	00000000 	nop
 490:	28422001 	slti	v0,v0,8193
 494:	1440ffef 	bnez	v0,454 <main+0x414>
 498:	00000000 	nop
 49c:	24060023 	li	a2,35
 4a0:	3c020000 	lui	v0,0x0
 4a4:	244507d8 	addiu	a1,v0,2008
 4a8:	24040001 	li	a0,1
 4ac:	0c0001ac 	jal	6b0 <write>
 4b0:	00000000 	nop
 4b4:	240601b6 	li	a2,438
 4b8:	24050241 	li	a1,577
 4bc:	3c020000 	lui	v0,0x0
 4c0:	244407fc 	addiu	a0,v0,2044
 4c4:	0c0001c0 	jal	700 <open>
 4c8:	00000000 	nop
 4cc:	afc20024 	sw	v0,36(s8)
 4d0:	24062001 	li	a2,8193
 4d4:	3c020000 	lui	v0,0x0
 4d8:	24450850 	addiu	a1,v0,2128
 4dc:	8fc40024 	lw	a0,36(s8)
 4e0:	0c0001ac 	jal	6b0 <write>
 4e4:	00000000 	nop
 4e8:	8fc40024 	lw	a0,36(s8)
 4ec:	0c0001d4 	jal	750 <close>
 4f0:	00000000 	nop
 4f4:	00001025 	move	v0,zero
 4f8:	10000013 	b	548 <main+0x508>
 4fc:	00000000 	nop
 500:	00000000 	nop
 504:	24060015 	li	a2,21
 508:	3c020000 	lui	v0,0x0
 50c:	24450808 	addiu	a1,v0,2056
 510:	24040001 	li	a0,1
 514:	0c0001ac 	jal	6b0 <write>
 518:	00000000 	nop
 51c:	2402ffff 	li	v0,-1
 520:	10000009 	b	548 <main+0x508>
 524:	00000000 	nop
 528:	00000000 	nop
 52c:	24060014 	li	a2,20
 530:	3c020000 	lui	v0,0x0
 534:	24450820 	addiu	a1,v0,2080
 538:	24040001 	li	a0,1
 53c:	0c0001ac 	jal	6b0 <write>
 540:	00000000 	nop
 544:	2402ffff 	li	v0,-1
 548:	03c0e825 	move	sp,s8
 54c:	8fbf0084 	lw	ra,132(sp)
 550:	8fbe0080 	lw	s8,128(sp)
 554:	8fb7007c 	lw	s7,124(sp)
 558:	8fb60078 	lw	s6,120(sp)
 55c:	8fb50074 	lw	s5,116(sp)
 560:	8fb40070 	lw	s4,112(sp)
 564:	8fb3006c 	lw	s3,108(sp)
 568:	8fb20068 	lw	s2,104(sp)
 56c:	8fb10064 	lw	s1,100(sp)
 570:	8fb00060 	lw	s0,96(sp)
 574:	27bd0088 	addiu	sp,sp,136
 578:	03e00008 	jr	ra
 57c:	00000000 	nop

00000580 <syscall_1>:
 580:	27bdfff0 	addiu	sp,sp,-16
 584:	afbe000c 	sw	s8,12(sp)
 588:	03a0f025 	move	s8,sp
 58c:	afc40010 	sw	a0,16(s8)
 590:	afc50014 	sw	a1,20(s8)
 594:	8fc30010 	lw	v1,16(s8)
 598:	8fc50014 	lw	a1,20(s8)
 59c:	00601025 	move	v0,v1
 5a0:	00a02025 	move	a0,a1
 5a4:	0000000c 	syscall
 5a8:	00801825 	move	v1,a0
 5ac:	afc30000 	sw	v1,0(s8)
 5b0:	8fc20000 	lw	v0,0(s8)
 5b4:	03c0e825 	move	sp,s8
 5b8:	8fbe000c 	lw	s8,12(sp)
 5bc:	27bd0010 	addiu	sp,sp,16
 5c0:	03e00008 	jr	ra
 5c4:	00000000 	nop

000005c8 <syscall_3>:
 5c8:	27bdfff0 	addiu	sp,sp,-16
 5cc:	afbe000c 	sw	s8,12(sp)
 5d0:	03a0f025 	move	s8,sp
 5d4:	afc40010 	sw	a0,16(s8)
 5d8:	afc50014 	sw	a1,20(s8)
 5dc:	afc60018 	sw	a2,24(s8)
 5e0:	afc7001c 	sw	a3,28(s8)
 5e4:	8fc30010 	lw	v1,16(s8)
 5e8:	8fc70014 	lw	a3,20(s8)
 5ec:	8fc80018 	lw	t0,24(s8)
 5f0:	8fc9001c 	lw	t1,28(s8)
 5f4:	00601025 	move	v0,v1
 5f8:	00e02025 	move	a0,a3
 5fc:	01002825 	move	a1,t0
 600:	01203025 	move	a2,t1
 604:	0000000c 	syscall
 608:	00801825 	move	v1,a0
 60c:	afc30000 	sw	v1,0(s8)
 610:	8fc20000 	lw	v0,0(s8)
 614:	03c0e825 	move	sp,s8
 618:	8fbe000c 	lw	s8,12(sp)
 61c:	27bd0010 	addiu	sp,sp,16
 620:	03e00008 	jr	ra
 624:	00000000 	nop

00000628 <exit>:
 628:	27bdfff8 	addiu	sp,sp,-8
 62c:	afbe0004 	sw	s8,4(sp)
 630:	03a0f025 	move	s8,sp
 634:	afc40008 	sw	a0,8(s8)
 638:	8fc30008 	lw	v1,8(s8)
 63c:	24020000 	li	v0,0
 640:	00602025 	move	a0,v1
 644:	0000000c 	syscall
 648:	00000000 	nop
 64c:	03c0e825 	move	sp,s8
 650:	8fbe0004 	lw	s8,4(sp)
 654:	27bd0008 	addiu	sp,sp,8
 658:	03e00008 	jr	ra
 65c:	00000000 	nop

00000660 <read>:
 660:	27bdffe8 	addiu	sp,sp,-24
 664:	afbf0014 	sw	ra,20(sp)
 668:	afbe0010 	sw	s8,16(sp)
 66c:	03a0f025 	move	s8,sp
 670:	afc40018 	sw	a0,24(s8)
 674:	afc5001c 	sw	a1,28(s8)
 678:	afc60020 	sw	a2,32(s8)
 67c:	8fc2001c 	lw	v0,28(s8)
 680:	8fc70020 	lw	a3,32(s8)
 684:	00403025 	move	a2,v0
 688:	8fc50018 	lw	a1,24(s8)
 68c:	24040001 	li	a0,1
 690:	0c000172 	jal	5c8 <syscall_3>
 694:	00000000 	nop
 698:	03c0e825 	move	sp,s8
 69c:	8fbf0014 	lw	ra,20(sp)
 6a0:	8fbe0010 	lw	s8,16(sp)
 6a4:	27bd0018 	addiu	sp,sp,24
 6a8:	03e00008 	jr	ra
 6ac:	00000000 	nop

000006b0 <write>:
 6b0:	27bdffe8 	addiu	sp,sp,-24
 6b4:	afbf0014 	sw	ra,20(sp)
 6b8:	afbe0010 	sw	s8,16(sp)
 6bc:	03a0f025 	move	s8,sp
 6c0:	afc40018 	sw	a0,24(s8)
 6c4:	afc5001c 	sw	a1,28(s8)
 6c8:	afc60020 	sw	a2,32(s8)
 6cc:	8fc2001c 	lw	v0,28(s8)
 6d0:	8fc70020 	lw	a3,32(s8)
 6d4:	00403025 	move	a2,v0
 6d8:	8fc50018 	lw	a1,24(s8)
 6dc:	24040002 	li	a0,2
 6e0:	0c000172 	jal	5c8 <syscall_3>
 6e4:	00000000 	nop
 6e8:	03c0e825 	move	sp,s8
 6ec:	8fbf0014 	lw	ra,20(sp)
 6f0:	8fbe0010 	lw	s8,16(sp)
 6f4:	27bd0018 	addiu	sp,sp,24
 6f8:	03e00008 	jr	ra
 6fc:	00000000 	nop

00000700 <open>:
 700:	27bdffe8 	addiu	sp,sp,-24
 704:	afbf0014 	sw	ra,20(sp)
 708:	afbe0010 	sw	s8,16(sp)
 70c:	03a0f025 	move	s8,sp
 710:	afc40018 	sw	a0,24(s8)
 714:	afc5001c 	sw	a1,28(s8)
 718:	afc60020 	sw	a2,32(s8)
 71c:	8fc20018 	lw	v0,24(s8)
 720:	8fc70020 	lw	a3,32(s8)
 724:	8fc6001c 	lw	a2,28(s8)
 728:	00402825 	move	a1,v0
 72c:	24040003 	li	a0,3
 730:	0c000172 	jal	5c8 <syscall_3>
 734:	00000000 	nop
 738:	03c0e825 	move	sp,s8
 73c:	8fbf0014 	lw	ra,20(sp)
 740:	8fbe0010 	lw	s8,16(sp)
 744:	27bd0018 	addiu	sp,sp,24
 748:	03e00008 	jr	ra
 74c:	00000000 	nop

00000750 <close>:
 750:	27bdffe8 	addiu	sp,sp,-24
 754:	afbf0014 	sw	ra,20(sp)
 758:	afbe0010 	sw	s8,16(sp)
 75c:	03a0f025 	move	s8,sp
 760:	afc40018 	sw	a0,24(s8)
 764:	8fc50018 	lw	a1,24(s8)
 768:	24040004 	li	a0,4
 76c:	0c000160 	jal	580 <syscall_1>
 770:	00000000 	nop
 774:	03c0e825 	move	sp,s8
 778:	8fbf0014 	lw	ra,20(sp)
 77c:	8fbe0010 	lw	s8,16(sp)
 780:	27bd0018 	addiu	sp,sp,24
 784:	03e00008 	jr	ra
 788:	00000000 	nop

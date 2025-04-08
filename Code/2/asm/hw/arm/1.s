.global obvod_trojuhelnika
.type obvod_trojuhelnika, %function
obvod_trojuhelnika:
  add w0, w0, w1
  add w0, w0, w2
  ret

.global objem_krychle
.type objem_krychle, %function
objem_krychle:
  mul w1, w0, w0
  mul w0, w1, w0
  ret

.global avg
.type avg, %function
avg:
  add w0, w0, w1
  add w0, w0, w2
  mov w1, #3
  sdiv w0, w0, w1
  ret

.global sgn
.type sgn, %function
sgn:
  cmp w0, #0
  cset w1, gt
  cset w2, lt
  sub w0, w1, w2
  ret

.global min3u
.type min3u, %function
min3u:
  cmp w0, w1
  csel w0, w1, w0, lo
  cmp w0, w2
  csel w0, w2, w0, lo
  ret

.global fact
.type fact, %function
fact:
  cmp w0, #1
  ble .Lfact_base
  stp x1, x30, [sp, #-16]!
  mov w1, w0
  sub w0, w0, #1
  bl fact
  mul w0, w0, w1
  ldp x1, x30, [sp], #16
  ret
.lfact_base:
  mov w0, #1
  ret

.global mocnina
.type mocnina, %function
mocnina:
  cmp w1, #0
  beq .Lpow_zero
  stp x2, x3, [sp, #-16]!
  mov w2, w0
  mov w3, #1
.lpow_loop:
  mul w3, w3, w2
  subs w1, w1, #1
  bne .Lpow_loop
  mov w0, w3
  ldp x2, x3, [sp], #16
  ret
.lpow_zero:
  mov w0, #1
  ret

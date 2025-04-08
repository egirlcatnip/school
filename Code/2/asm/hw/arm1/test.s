.global _start

_start:
  MOV x0, #1
  MOV x1, #2
  ADD x2, x1, x0

_exit:
  MOV x8, #93
  MOV x0, #0
  SVC #0

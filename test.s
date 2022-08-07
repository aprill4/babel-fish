.arch armv8-a
.text
.align 2
.syntax unified
.arm
.global main
z:
z27:
  bx	lr

main:
main28:
  mov	fp, sp
  sub	sp, sp, #16
  sub	vg0, fp, #12
  mov	vg1, #0
  str	vg1, [vg0]
  sub	vg2, fp, #12
  add	vg2, vg2, #4
  str	vg1, [vg2]
  sub	vg3, fp, #12
  add	vg3, vg3, #8
  str	vg1, [vg3]
  sub	vg4, fp, #12
  add	vg4, vg4, #4
  mov	vg5, #3
  str	vg5, [vg4]
  movw	vg6, #26214
  movt	vg6, #16294
  vmov	vf7, vg6
  vstr	vg6, [fp, #-16]
  movw	vg8, #26214
  movt	vg8, #16294
  vmov	vf9, vg8
  vmov.f32	s0, vg8
  add	sp, sp, #16
  bx	lr


@ here are the globals +-+^_^+-=
x:
  .word	1

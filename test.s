.arch armv8-a
.text
.align 2
.syntax unified
.arm
.global main
main:
main27:
  mov	fp, sp
  sub	sp, sp, #20
  mov	vg0, #2
  str	vg0, [fp, #-4]
  mov	vg1, #1
  str	vg1, [fp, #-8]
  ldr	vg2, [fp, #-4]
  ldr	vg3, [fp, #-8]
  add	vg4, vg2, vg3
  mov	vg5, #2
  mul	vg6, vg4, vg5
  str	vg6, [fp, #-12]
  ldr	vg7, [fp, #-8]
  sub	vg8, vg7, #1
  str	vg8, [fp, #-16]
  movw	vg9, #26214
  movt	vg9, #16294
  vmov	vf10, vg9
  vstr	vg9, [fp, #-20]
  bx	lr
  movw	vg11, #26214
  movt	vg11, #16294
  vmov.f32	s0, vg11
  add	sp, sp, #20
  vmov	vf12, vg11


@ here are the globals +-+^_^+-=
x:
  .word	1

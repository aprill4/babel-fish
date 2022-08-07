.arch armv8-a
.text
.align 2
.syntax unified
.arm
.global main
main:
main24:
  mov	fp, sp
  sub	sp, sp, #8
  movw	vg0, #0
  movt	vg0, #16448
  vmov	vf1, vg0
  vstr	vg0, [fp, #-4]
  vldr	vf2, [fp, #-4]
  mov	vg3, #1065353216
  vmov	vf4, vg3
  vadd.f32	vf5, vf2, vg3
  vstr	vf5, [fp, #-8]
  mov	r0, #1
  add	sp, sp, #8
  bx	lr


@ here are the globals +-+^_^+-=

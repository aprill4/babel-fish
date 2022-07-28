@a10 = global i32 1
@b13 = global i32 0
@c16 = global i32 1
@d19 = global i32 2
@e22 = global i32 4
define void @putint(i32 ) {
putint1:
  ret void
}
define void @putch(i32 ) {
putch3:
  ret void
}
define i32 @getint() {
getint4:
  ret i32 0
}
define i32 @getch() {
getch6:
  ret i32 0
}
define i32 @main() {
main23:
  %v24 = alloca i32
  store i32 0, i32* %v24
  %v33 = load i32, i32* @a10
  %v34 = load i32, i32* @b13
  %v35 = mul i32 %v33, %v34
  %v36 = load i32, i32* @c16
  %v37 = sdiv i32 %v35, %v36
  %v38 = load i32, i32* @e22
  %v39 = load i32, i32* @d19
  %v40 = add nsw i32 %v38, %v39
  %bool_41 = icmp eq i32 %v37, %v40
  %bool_43 = icmp ne i1 %bool_41, zeroinitializer
  br i1 %bool_43, label %l31, label %r32
if_true_entry26:
  store i32 1, i32* %v24
  br label %next_entry28
next_entry28:
  %v71 = load i32, i32* %v24
  call void @putint(i32 %v71)
  %v73 = load i32, i32* %v24
  ret i32 %v73
l29:
  br label %if_true_entry26
r30:
  %v57 = load i32, i32* @a10
  %v58 = load i32, i32* @b13
  %v59 = load i32, i32* @c16
  %v60 = mul i32 %v58, %v59
  %v61 = sub nsw i32 %v57, %v60
  %v62 = load i32, i32* @d19
  %v63 = load i32, i32* @a10
  %v64 = load i32, i32* @c16
  %v65 = sdiv i32 %v63, %v64
  %v66 = sub nsw i32 %v62, %v65
  %bool_67 = icmp eq i32 %v61, %v66
  %bool_69 = icmp ne i1 %bool_67, zeroinitializer
  br i1 %bool_69, label %l29, label %next_entry28
l31:
  %v44 = load i32, i32* @a10
  %v45 = load i32, i32* @a10
  %v46 = load i32, i32* @b13
  %v47 = add nsw i32 %v45, %v46
  %v48 = mul i32 %v44, %v47
  %v49 = load i32, i32* @c16
  %v50 = add nsw i32 %v48, %v49
  %v51 = load i32, i32* @d19
  %v52 = load i32, i32* @e22
  %v53 = add nsw i32 %v51, %v52
  %bool_54 = icmp sle i32 %v50, %v53
  %bool_56 = icmp ne i1 %bool_54, zeroinitializer
  br i1 %bool_56, label %if_true_entry26, label %r32
r32:
  br label %next_entry28
}


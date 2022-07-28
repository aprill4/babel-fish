@k9 = global i32 zeroinitializer
@n12 = constant i32 10
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
main13:
  %v14 = alloca i32
  store i32 0, i32* %v14
  store i32 1, i32* @k9
  %v19 = load i32, i32* %v14
  %bool_22 = icmp sle i32 %v19, 9
  %bool_24 = icmp ne i1 %bool_22, false
  br i1 %bool_24, label %while_entry17, label %next_entry18
while_entry17:
  %v25 = load i32, i32* %v14
  %v27 = add nsw i32 %v25, 1
  store i32 %v27, i32* %v14
  %v28 = load i32, i32* @k9
  %v30 = add nsw i32 %v28, 1
  %v31 = load i32, i32* @k9
  %v32 = load i32, i32* @k9
  %v33 = add nsw i32 %v31, %v32
  store i32 %v33, i32* @k9
  br i1 %bool_24, label %while_entry17, label %next_entry18
next_entry18:
  %v34 = load i32, i32* @k9
  call void @putint(i32 %v34)
  %v36 = load i32, i32* @k9
  ret i32 %v36
}


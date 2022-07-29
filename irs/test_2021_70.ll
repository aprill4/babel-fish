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
main8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  store i32 0, i32* %v11
  store i32 0, i32* %v9
  %v17 = load i32, i32* %v9
  %bool_19 = icmp slt i32 %v17, 21
  %bool_21 = icmp ne i1 %bool_19, false
  br i1 %bool_21, label %while_entry15, label %next_entry16
while_entry15:
  %v22 = load i32, i32* %v11
  %v23 = load i32, i32* %v9
  %v24 = mul i32 %v22, %v23
  store i32 %v24, i32* %v11
  %v25 = load i32, i32* %v9
  %v27 = add nsw i32 %v25, 1
  store i32 %v27, i32* %v9
  br i1 %bool_21, label %while_entry15, label %next_entry16
next_entry16:
  %v28 = load i32, i32* %v11
  call void @putint(i32 %v28)
  ret i32 0
}


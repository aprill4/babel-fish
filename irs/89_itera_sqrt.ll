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
define i32 @fsqrt(i32 ) {
fsqrt9:
  %v10 = alloca i32
  %v11 = alloca i32
  store i32 0, i32* %v11
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = load i32, i32* %v10
  %v17 = sdiv i32 %v15, 2
  store i32 %v17, i32* %v13
  %v20 = load i32, i32* %v11
  %v21 = load i32, i32* %v13
  %v22 = sub nsw i32 %v20, %v21
  %bool_24 = icmp ne i32 %v22, 0
  %bool_26 = icmp ne i1 %bool_24, false
  br i1 %bool_26, label %while_entry18, label %next_entry19
while_entry18:
  %v27 = load i32, i32* %v13
  store i32 %v27, i32* %v11
  %v28 = load i32, i32* %v11
  %v29 = load i32, i32* %v10
  %v30 = load i32, i32* %v11
  %v31 = sdiv i32 %v29, %v30
  %v32 = add nsw i32 %v28, %v31
  store i32 %v32, i32* %v13
  %v33 = load i32, i32* %v13
  %v35 = sdiv i32 %v33, 2
  store i32 %v35, i32* %v13
  br i1 %bool_26, label %while_entry18, label %next_entry19
next_entry19:
  %v36 = load i32, i32* %v13
  ret i32 %v36
}
define i32 @main() {
main37:
  %v38 = alloca i32
  store i32 zeroinitializer, i32* %v38
  store i32 400, i32* %v38
  %v41 = alloca i32
  store i32 zeroinitializer, i32* %v41
  %v43 = load i32, i32* %v38
  %v44 = call i32 @fsqrt(i32 %v43)
  store i32 %v44, i32* %v41
  %v45 = load i32, i32* %v41
  call void @putint(i32 %v45)
  store i32 10, i32* %v41
  %v48 = load i32, i32* %v41
  call void @putch(i32 %v48)
  ret i32 0
}


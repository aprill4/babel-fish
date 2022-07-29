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
define i32 @dec2bin(i32 ) {
dec2bin9:
  %v10 = alloca i32
  %v11 = alloca i32
  store i32 zeroinitializer, i32* %v11
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  store i32 0, i32* %v11
  store i32 1, i32* %v13
  %v21 = load i32, i32* %v10
  store i32 %v21, i32* %v17
  %v24 = load i32, i32* %v17
  %bool_26 = icmp ne i32 %v24, 0
  %bool_28 = icmp ne i1 %bool_26, false
  br i1 %bool_28, label %while_entry22, label %next_entry23
while_entry22:
  %v29 = load i32, i32* %v17
  %v31 = srem i32 %v29, 2
  store i32 %v31, i32* %v15
  %v32 = load i32, i32* %v13
  %v33 = load i32, i32* %v15
  %v34 = mul i32 %v32, %v33
  %v35 = load i32, i32* %v11
  %v36 = add nsw i32 %v34, %v35
  store i32 %v36, i32* %v11
  %v37 = load i32, i32* %v13
  %v39 = mul i32 %v37, 10
  store i32 %v39, i32* %v13
  %v40 = load i32, i32* %v17
  %v42 = sdiv i32 %v40, 2
  store i32 %v42, i32* %v17
  br i1 %bool_28, label %while_entry22, label %next_entry23
next_entry23:
  %v43 = load i32, i32* %v11
  ret i32 %v43
}
define i32 @main() {
main44:
  %v45 = alloca i32
  store i32 zeroinitializer, i32* %v45
  store i32 400, i32* %v45
  %v48 = alloca i32
  store i32 zeroinitializer, i32* %v48
  %v50 = load i32, i32* %v45
  %v51 = call i32 @dec2bin(i32 %v50)
  store i32 %v51, i32* %v48
  %v52 = load i32, i32* %v48
  call void @putint(i32 %v52)
  store i32 10, i32* %v48
  %v55 = load i32, i32* %v48
  call void @putch(i32 %v55)
  ret i32 0
}


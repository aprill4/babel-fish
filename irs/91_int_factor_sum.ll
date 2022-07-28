@N9 = global i32 zeroinitializer
@newline11 = global i32 zeroinitializer
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
define i32 @factor(i32 ) {
factor13:
  %v14 = alloca i32
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  %v17 = alloca i32
  store i32 zeroinitializer, i32* %v17
  store i32 0, i32* %v17
  store i32 1, i32* %v15
  %v23 = load i32, i32* %v15
  %v24 = load i32, i32* %v14
  %v26 = add nsw i32 %v24, 1
  %bool_27 = icmp slt i32 %v23, %v26
  %bool_29 = icmp ne i1 %bool_27, false
  br i1 %bool_29, label %while_entry21, label %next_entry22
while_entry21:
  %v33 = load i32, i32* %v14
  %v34 = load i32, i32* %v15
  %v35 = srem i32 %v33, %v34
  %bool_37 = icmp eq i32 %v35, 0
  br i1 %bool_37, label %if_true_entry30, label %next_entry32
next_entry22:
  %v44 = load i32, i32* %v17
  ret i32 %v44
if_true_entry30:
  %v38 = load i32, i32* %v17
  %v39 = load i32, i32* %v15
  %v40 = add nsw i32 %v38, %v39
  store i32 %v40, i32* %v17
  br label %next_entry32
next_entry32:
  %v41 = load i32, i32* %v15
  %v43 = add nsw i32 %v41, 1
  store i32 %v43, i32* %v15
  br i1 %bool_29, label %while_entry21, label %next_entry22
}
define i32 @main() {
main45:
  store i32 4, i32* @N9
  store i32 10, i32* @newline11
  %v48 = alloca i32
  store i32 zeroinitializer, i32* %v48
  %v50 = alloca i32
  store i32 zeroinitializer, i32* %v50
  store i32 1478, i32* %v50
  %v53 = alloca i32
  store i32 zeroinitializer, i32* %v53
  %v55 = load i32, i32* %v50
  %v56 = call i32 @factor(i32 %v55)
  ret i32 %v56
}


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
define i32 @enc(i32 ) {
enc9:
  %v10 = alloca i32
  %v14 = load i32, i32* %v10
  %bool_16 = icmp sgt i32 %v14, 25
  br i1 %bool_16, label %if_true_entry11, label %if_false_entry12
if_true_entry11:
  %v17 = load i32, i32* %v10
  %v19 = add nsw i32 %v17, 60
  store i32 %v19, i32* %v10
  br label %next_entry13
if_false_entry12:
  %v20 = load i32, i32* %v10
  %v22 = sub nsw i32 %v20, 15
  store i32 %v22, i32* %v10
  br label %next_entry13
next_entry13:
  %v23 = load i32, i32* %v10
  ret i32 %v23
}
define i32 @dec(i32 ) {
dec25:
  %v26 = alloca i32
  %v30 = load i32, i32* %v26
  %bool_32 = icmp sgt i32 %v30, 85
  br i1 %bool_32, label %if_true_entry27, label %if_false_entry28
if_true_entry27:
  %v33 = load i32, i32* %v26
  %v35 = sub nsw i32 %v33, 59
  store i32 %v35, i32* %v26
  br label %next_entry29
if_false_entry28:
  %v36 = load i32, i32* %v26
  %v38 = add nsw i32 %v36, 14
  store i32 %v38, i32* %v26
  br label %next_entry29
next_entry29:
  %v39 = load i32, i32* %v26
  ret i32 %v39
}
define i32 @main() {
main40:
  %v41 = alloca i32
  store i32 zeroinitializer, i32* %v41
  store i32 400, i32* %v41
  %v44 = alloca i32
  store i32 zeroinitializer, i32* %v44
  %v46 = load i32, i32* %v41
  %v47 = call i32 @enc(i32 %v46)
  store i32 %v47, i32* %v44
  %v48 = load i32, i32* %v44
  %v49 = call i32 @dec(i32 %v48)
  store i32 %v49, i32* %v44
  %v50 = load i32, i32* %v44
  call void @putint(i32 %v50)
  store i32 10, i32* %v44
  %v53 = load i32, i32* %v44
  call void @putch(i32 %v53)
  ret i32 0
}


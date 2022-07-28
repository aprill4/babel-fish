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
  store i32 56, i32* %v9
  store i32 4, i32* %v11
  %v15 = load i32, i32* %v9
  %v18 = sub nsw i32 0, 4
  %v19 = sub nsw i32 %v15, %v18
  %v20 = load i32, i32* %v11
  %v21 = add nsw i32 %v19, %v20
  store i32 %v21, i32* %v9
  %v25 = load i32, i32* %v9
  %bool_27 = icmp ne i32 %v25, zeroinitializer
  %bool_29 = icmp eq i1 %bool_27, zeroinitializer
  %bool_31 = icmp ne i1 %bool_29, zeroinitializer
  %bool_33 = icmp eq i1 %bool_31, zeroinitializer
  %bool_35 = icmp ne i1 %bool_33, zeroinitializer
  %bool_37 = icmp eq i1 %bool_35, zeroinitializer
  %v39 = sub nsw i1 false, %bool_37
  br i1 %v39, label %if_true_entry22, label %if_false_entry23
if_true_entry22:
  %v42 = sub nsw i32 0, 1
  %v44 = sub nsw i32 0, %v42
  %v46 = sub nsw i32 0, %v44
  store i32 %v46, i32* %v9
  br label %next_entry24
if_false_entry23:
  %v48 = load i32, i32* %v11
  %v49 = add nsw i32 0, %v48
  store i32 %v49, i32* %v9
  br label %next_entry24
next_entry24:
  %v50 = load i32, i32* %v9
  call void @putint(i32 %v50)
  ret i32 0
}


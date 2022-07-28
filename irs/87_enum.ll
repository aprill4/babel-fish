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
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  store i32 0, i32* %v9
  store i32 0, i32* %v11
  store i32 0, i32* %v13
  %v22 = load i32, i32* %v9
  %bool_24 = icmp slt i32 %v22, 21
  %bool_26 = icmp ne i1 %bool_24, false
  br i1 %bool_26, label %while_entry20, label %next_entry21
while_entry20:
  %v29 = load i32, i32* %v11
  %v31 = load i32, i32* %v9
  %v32 = sub nsw i32 101, %v31
  %bool_33 = icmp slt i32 %v29, %v32
  %bool_35 = icmp ne i1 %bool_33, false
  br i1 %bool_35, label %while_entry27, label %next_entry28
next_entry21:
  ret i32 0
while_entry27:
  %v37 = load i32, i32* %v9
  %v38 = sub nsw i32 100, %v37
  %v39 = load i32, i32* %v11
  %v40 = sub nsw i32 %v38, %v39
  store i32 %v40, i32* %v13
  %v45 = load i32, i32* %v9
  %v46 = mul i32 5, %v45
  %v48 = load i32, i32* %v11
  %v49 = mul i32 1, %v48
  %v50 = add nsw i32 %v46, %v49
  %v51 = load i32, i32* %v13
  %v53 = sdiv i32 %v51, 2
  %v54 = add nsw i32 %v50, %v53
  %bool_56 = icmp eq i32 %v54, 100
  br i1 %bool_56, label %if_true_entry41, label %next_entry43
next_entry28:
  %v69 = load i32, i32* %v9
  %v71 = add nsw i32 %v69, 1
  store i32 %v71, i32* %v9
  br i1 %bool_26, label %while_entry20, label %next_entry21
if_true_entry41:
  %v57 = load i32, i32* %v9
  call void @putint(i32 %v57)
  %v59 = load i32, i32* %v11
  call void @putint(i32 %v59)
  %v61 = load i32, i32* %v13
  call void @putint(i32 %v61)
  store i32 10, i32* %v15
  %v64 = load i32, i32* %v15
  call void @putch(i32 %v64)
  br label %next_entry43
next_entry43:
  %v66 = load i32, i32* %v11
  %v68 = add nsw i32 %v66, 1
  store i32 %v68, i32* %v11
  br i1 %bool_35, label %while_entry27, label %next_entry28
}


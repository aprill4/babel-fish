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
define i32 @FourWhile() {
FourWhile8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 5, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  %v14 = alloca i32
  store i32 zeroinitializer, i32* %v14
  store i32 6, i32* %v12
  store i32 7, i32* %v14
  %v18 = alloca i32
  store i32 zeroinitializer, i32* %v18
  store i32 10, i32* %v18
  %v23 = load i32, i32* %v9
  %bool_25 = icmp slt i32 %v23, 20
  %bool_27 = icmp ne i1 %bool_25, false
  br i1 %bool_27, label %while_entry21, label %next_entry22
while_entry21:
  %v28 = load i32, i32* %v9
  %v30 = add nsw i32 %v28, 3
  store i32 %v30, i32* %v9
  %v33 = load i32, i32* %v12
  %bool_35 = icmp slt i32 %v33, 10
  %bool_37 = icmp ne i1 %bool_35, false
  br i1 %bool_37, label %while_entry31, label %next_entry32
next_entry22:
  %v70 = load i32, i32* %v9
  %v71 = load i32, i32* %v12
  %v72 = load i32, i32* %v18
  %v73 = add nsw i32 %v71, %v72
  %v74 = add nsw i32 %v70, %v73
  %v75 = load i32, i32* %v14
  %v76 = add nsw i32 %v74, %v75
  ret i32 %v76
while_entry31:
  %v38 = load i32, i32* %v12
  %v40 = add nsw i32 %v38, 1
  store i32 %v40, i32* %v12
  %v43 = load i32, i32* %v14
  %bool_45 = icmp eq i32 %v43, 7
  %bool_47 = icmp ne i1 %bool_45, false
  br i1 %bool_47, label %while_entry41, label %next_entry42
next_entry32:
  %v67 = load i32, i32* %v12
  %v69 = sub nsw i32 %v67, 2
  store i32 %v69, i32* %v12
  br i1 %bool_27, label %while_entry21, label %next_entry22
while_entry41:
  %v48 = load i32, i32* %v14
  %v50 = sub nsw i32 %v48, 1
  store i32 %v50, i32* %v14
  %v53 = load i32, i32* %v18
  %bool_55 = icmp slt i32 %v53, 20
  %bool_57 = icmp ne i1 %bool_55, false
  br i1 %bool_57, label %while_entry51, label %next_entry52
next_entry42:
  %v64 = load i32, i32* %v14
  %v66 = add nsw i32 %v64, 1
  store i32 %v66, i32* %v14
  br i1 %bool_37, label %while_entry31, label %next_entry32
while_entry51:
  %v58 = load i32, i32* %v18
  %v60 = add nsw i32 %v58, 3
  store i32 %v60, i32* %v18
  br i1 %bool_57, label %while_entry51, label %next_entry52
next_entry52:
  %v61 = load i32, i32* %v18
  %v63 = sub nsw i32 %v61, 1
  store i32 %v63, i32* %v18
  br i1 %bool_47, label %while_entry41, label %next_entry42
}
define i32 @main() {
main77:
  %v78 = call i32 @FourWhile()
  ret i32 %v78
}


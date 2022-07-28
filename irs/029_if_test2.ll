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
define i32 @ifElseIf() {
ifElseIf8:
  %v9 = alloca i32
  store i32 zeroinitializer, i32* %v9
  store i32 5, i32* %v9
  %v12 = alloca i32
  store i32 zeroinitializer, i32* %v12
  store i32 10, i32* %v12
  %v20 = load i32, i32* %v9
  %bool_22 = icmp eq i32 %v20, 6
  %bool_24 = icmp ne i1 %bool_22, zeroinitializer
  br i1 %bool_24, label %l18, label %r19
if_true_entry15:
  %v30 = load i32, i32* %v9
  ret i32 %v30
if_false_entry16:
  %v36 = load i32, i32* %v12
  %bool_38 = icmp eq i32 %v36, 10
  %bool_40 = icmp ne i1 %bool_38, zeroinitializer
  br i1 %bool_40, label %l34, label %r35
next_entry17:
  %v70 = load i32, i32* %v9
  ret i32 %v70
l18:
  br label %if_true_entry15
r19:
  %v25 = load i32, i32* %v12
  %bool_27 = icmp eq i32 %v25, 11
  %bool_29 = icmp ne i1 %bool_27, zeroinitializer
  br i1 %bool_29, label %l18, label %if_false_entry16
if_true_entry31:
  store i32 25, i32* %v9
  br label %next_entry33
if_false_entry32:
  %v52 = load i32, i32* %v12
  %bool_54 = icmp eq i32 %v52, 10
  %bool_56 = icmp ne i1 %bool_54, zeroinitializer
  br i1 %bool_56, label %l50, label %r51
next_entry33:
  br label %next_entry17
l34:
  %v41 = load i32, i32* %v9
  %bool_43 = icmp eq i32 %v41, 1
  %bool_45 = icmp ne i1 %bool_43, zeroinitializer
  br i1 %bool_45, label %if_true_entry31, label %r35
r35:
  br label %if_false_entry32
if_true_entry47:
  %v64 = load i32, i32* %v9
  %v66 = add nsw i32 %v64, 15
  store i32 %v66, i32* %v9
  br label %next_entry49
if_false_entry48:
  %v67 = load i32, i32* %v9
  %v69 = sub nsw i32 0, %v67
  store i32 %v69, i32* %v9
  br label %next_entry49
next_entry49:
  br label %next_entry33
l50:
  %v57 = load i32, i32* %v9
  %v60 = sub nsw i32 0, 5
  %bool_61 = icmp eq i32 %v57, %v60
  %bool_63 = icmp ne i1 %bool_61, zeroinitializer
  br i1 %bool_63, label %if_true_entry47, label %r51
r51:
  br label %if_false_entry48
}
define i32 @main() {
main71:
  %v72 = call i32 @ifElseIf()
  call void @putint(i32 %v72)
  ret i32 0
}


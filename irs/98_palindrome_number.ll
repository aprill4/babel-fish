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
define i32 @palindrome(i32 ) {
palindrome9:
  %v10 = alloca i32
  %v13 = alloca [4 x i32]
  %v16 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 0
  store i32 zeroinitializer, i32* %v16
  %v18 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 1
  store i32 zeroinitializer, i32* %v18
  %v20 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 2
  store i32 zeroinitializer, i32* %v20
  %v22 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 3
  store i32 zeroinitializer, i32* %v22
  %v23 = alloca i32
  store i32 zeroinitializer, i32* %v23
  %v25 = alloca i32
  store i32 zeroinitializer, i32* %v25
  store i32 0, i32* %v23
  %v30 = load i32, i32* %v23
  %bool_32 = icmp slt i32 %v30, 4
  %bool_34 = icmp ne i1 %bool_32, false
  br i1 %bool_34, label %while_entry28, label %next_entry29
while_entry28:
  %v35 = load i32, i32* %v23
  %v36 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 %v35
  %v37 = load i32, i32* %v10
  %v39 = srem i32 %v37, 10
  store i32 %v39, i32* %v36
  %v40 = load i32, i32* %v10
  %v42 = sdiv i32 %v40, 10
  store i32 %v42, i32* %v10
  %v43 = load i32, i32* %v23
  %v45 = add nsw i32 %v43, 1
  store i32 %v45, i32* %v23
  br i1 %bool_34, label %while_entry28, label %next_entry29
next_entry29:
  %v53 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 0
  %v54 = load i32, i32* %v53
  %v57 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 3
  %v58 = load i32, i32* %v57
  %bool_59 = icmp eq i32 %v54, %v58
  %bool_61 = icmp ne i1 %bool_59, zeroinitializer
  br i1 %bool_61, label %l49, label %r50
if_true_entry46:
  store i32 1, i32* %v25
  br label %next_entry48
if_false_entry47:
  store i32 0, i32* %v25
  br label %next_entry48
next_entry48:
  %v75 = load i32, i32* %v25
  ret i32 %v75
l49:
  %v64 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 1
  %v65 = load i32, i32* %v64
  %v68 = getelementptr [4 x i32], [4 x i32]* %v13, i32 0, i32 2
  %v69 = load i32, i32* %v68
  %bool_70 = icmp eq i32 %v65, %v69
  %bool_72 = icmp ne i1 %bool_70, zeroinitializer
  br i1 %bool_72, label %if_true_entry46, label %r50
r50:
  br label %if_false_entry47
}
define i32 @main() {
main76:
  %v77 = alloca i32
  store i32 zeroinitializer, i32* %v77
  store i32 1221, i32* %v77
  %v80 = alloca i32
  store i32 zeroinitializer, i32* %v80
  %v82 = load i32, i32* %v77
  %v83 = call i32 @palindrome(i32 %v82)
  store i32 %v83, i32* %v80
  %v87 = load i32, i32* %v80
  %bool_89 = icmp eq i32 %v87, 1
  br i1 %bool_89, label %if_true_entry84, label %if_false_entry85
if_true_entry84:
  %v90 = load i32, i32* %v77
  call void @putint(i32 %v90)
  br label %next_entry86
if_false_entry85:
  store i32 0, i32* %v80
  %v93 = load i32, i32* %v80
  call void @putint(i32 %v93)
  br label %next_entry86
next_entry86:
  store i32 10, i32* %v80
  %v96 = load i32, i32* %v80
  call void @putch(i32 %v96)
  ret i32 0
}


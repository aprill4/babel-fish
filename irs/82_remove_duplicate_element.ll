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
define i32 @removeElement(i32* , i32 , i32 ) {
removeElement11:
  %v12 = alloca i32
  %v13 = alloca i32
  %v14 = alloca i32
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  store i32 0, i32* %v15
  %v20 = load i32, i32* %v15
  %v21 = load i32, i32* %v13
  %bool_22 = icmp slt i32 %v20, %v21
  %bool_24 = icmp ne i1 %bool_22, false
  br i1 %bool_24, label %while_entry18, label %next_entry19
while_entry18:
  %v28 = load i32, i32* %v15
  %v29 = getelementptr i32, i32* %v12, i32 0, i32 %v28
  %v30 = load i32, i32* %v29
  %v31 = load i32, i32* %v14
  %bool_32 = icmp eq i32 %v30, %v31
  br i1 %bool_32, label %if_true_entry25, label %if_false_entry26
next_entry19:
  %v46 = load i32, i32* %v13
  ret i32 %v46
if_true_entry25:
  %v33 = load i32, i32* %v15
  %v34 = getelementptr i32, i32* %v12, i32 0, i32 %v33
  %v35 = load i32, i32* %v13
  %v37 = sub nsw i32 %v35, 1
  %v38 = getelementptr i32, i32* %v12, i32 0, i32 %v37
  %v39 = load i32, i32* %v38
  store i32 %v39, i32* %v34
  %v40 = load i32, i32* %v13
  %v42 = sub nsw i32 %v40, 1
  store i32 %v42, i32* %v13
  br label %next_entry27
if_false_entry26:
  %v43 = load i32, i32* %v15
  %v45 = add nsw i32 %v43, 1
  store i32 %v45, i32* %v15
  br label %next_entry27
next_entry27:
  br i1 %bool_24, label %while_entry18, label %next_entry19
}
define i32 @main() {
main47:
  %v48 = alloca i32
  store i32 zeroinitializer, i32* %v48
  %v52 = alloca [10 x i32]
  %v55 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 0
  store i32 zeroinitializer, i32* %v55
  %v57 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 1
  store i32 zeroinitializer, i32* %v57
  %v59 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 2
  store i32 zeroinitializer, i32* %v59
  %v61 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 3
  store i32 zeroinitializer, i32* %v61
  %v63 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 4
  store i32 zeroinitializer, i32* %v63
  %v65 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 5
  store i32 zeroinitializer, i32* %v65
  %v67 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 6
  store i32 zeroinitializer, i32* %v67
  %v69 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 7
  store i32 zeroinitializer, i32* %v69
  %v71 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 8
  store i32 zeroinitializer, i32* %v71
  %v73 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 9
  store i32 zeroinitializer, i32* %v73
  %v76 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 0
  store i32 3, i32* %v76
  %v80 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 1
  store i32 3, i32* %v80
  %v84 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 2
  store i32 9, i32* %v84
  %v88 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 3
  store i32 0, i32* %v88
  %v92 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 4
  store i32 0, i32* %v92
  %v96 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 5
  store i32 1, i32* %v96
  %v100 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 6
  store i32 1, i32* %v100
  %v104 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 7
  store i32 5, i32* %v104
  %v108 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 8
  store i32 7, i32* %v108
  %v112 = getelementptr [10 x i32], [10 x i32]* %v52, i32 0, i32 9
  store i32 8, i32* %v112
  store i32 10, i32* %v48
  %v115 = alloca i32
  store i32 zeroinitializer, i32* %v115
  store i32 3, i32* %v115
  %v118 = load [10 x i32], [10 x i32]* %v52
  %v119 = load i32, i32* %v48
  %v120 = load i32, i32* %v115
  %v121 = call i32 @removeElement([10 x i32] %v118, i32 %v119, i32 %v120)
  store i32 %v121, i32* %v48
  %v122 = load i32, i32* %v48
  ret i32 %v122
}


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
define i32 @maxArea(i32* , i32 ) {
maxArea10:
  %v11 = alloca i32
  %v12 = alloca i32
  %v13 = alloca i32
  store i32 zeroinitializer, i32* %v13
  %v15 = alloca i32
  store i32 zeroinitializer, i32* %v15
  store i32 0, i32* %v13
  %v18 = load i32, i32* %v12
  %v20 = sub nsw i32 %v18, 1
  store i32 %v20, i32* %v15
  %v21 = alloca i32
  store i32 zeroinitializer, i32* %v21
  %v25 = sub nsw i32 0, 1
  store i32 %v25, i32* %v21
  %v28 = load i32, i32* %v13
  %v29 = load i32, i32* %v15
  %bool_30 = icmp slt i32 %v28, %v29
  %bool_32 = icmp ne i1 %bool_30, false
  br i1 %bool_32, label %while_entry26, label %next_entry27
while_entry26:
  %v33 = alloca i32
  store i32 zeroinitializer, i32* %v33
  %v38 = load i32, i32* %v13
  %v39 = getelementptr i32, i32* %v11, i32 0, i32 %v38
  %v40 = load i32, i32* %v39
  %v41 = load i32, i32* %v15
  %v42 = getelementptr i32, i32* %v11, i32 0, i32 %v41
  %v43 = load i32, i32* %v42
  %bool_44 = icmp slt i32 %v40, %v43
  br i1 %bool_44, label %if_true_entry35, label %if_false_entry36
next_entry27:
  %v82 = load i32, i32* %v21
  ret i32 %v82
if_true_entry35:
  %v45 = load i32, i32* %v15
  %v46 = load i32, i32* %v13
  %v47 = sub nsw i32 %v45, %v46
  %v48 = load i32, i32* %v13
  %v49 = getelementptr i32, i32* %v11, i32 0, i32 %v48
  %v50 = load i32, i32* %v49
  %v51 = mul i32 %v47, %v50
  store i32 %v51, i32* %v33
  br label %next_entry37
if_false_entry36:
  %v52 = load i32, i32* %v15
  %v53 = load i32, i32* %v13
  %v54 = sub nsw i32 %v52, %v53
  %v55 = load i32, i32* %v15
  %v56 = getelementptr i32, i32* %v11, i32 0, i32 %v55
  %v57 = load i32, i32* %v56
  %v58 = mul i32 %v54, %v57
  store i32 %v58, i32* %v33
  br label %next_entry37
next_entry37:
  %v62 = load i32, i32* %v33
  %v63 = load i32, i32* %v21
  %bool_64 = icmp sgt i32 %v62, %v63
  br i1 %bool_64, label %if_true_entry59, label %next_entry61
if_true_entry59:
  %v65 = load i32, i32* %v33
  store i32 %v65, i32* %v21
  br label %next_entry61
next_entry61:
  %v69 = load i32, i32* %v13
  %v70 = getelementptr i32, i32* %v11, i32 0, i32 %v69
  %v71 = load i32, i32* %v70
  %v72 = load i32, i32* %v15
  %v73 = getelementptr i32, i32* %v11, i32 0, i32 %v72
  %v74 = load i32, i32* %v73
  %bool_75 = icmp sgt i32 %v71, %v74
  br i1 %bool_75, label %if_true_entry66, label %if_false_entry67
if_true_entry66:
  %v76 = load i32, i32* %v15
  %v78 = sub nsw i32 %v76, 1
  store i32 %v78, i32* %v15
  br label %next_entry68
if_false_entry67:
  %v79 = load i32, i32* %v13
  %v81 = add nsw i32 %v79, 1
  store i32 %v81, i32* %v13
  br label %next_entry68
next_entry68:
  br i1 %bool_32, label %while_entry26, label %next_entry27
}
define i32 @main() {
main83:
  %v84 = alloca i32
  store i32 zeroinitializer, i32* %v84
  %v88 = alloca [10 x i32]
  %v91 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 0
  store i32 zeroinitializer, i32* %v91
  %v93 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 1
  store i32 zeroinitializer, i32* %v93
  %v95 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 2
  store i32 zeroinitializer, i32* %v95
  %v97 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 3
  store i32 zeroinitializer, i32* %v97
  %v99 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 4
  store i32 zeroinitializer, i32* %v99
  %v101 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 5
  store i32 zeroinitializer, i32* %v101
  %v103 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 6
  store i32 zeroinitializer, i32* %v103
  %v105 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 7
  store i32 zeroinitializer, i32* %v105
  %v107 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 8
  store i32 zeroinitializer, i32* %v107
  %v109 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 9
  store i32 zeroinitializer, i32* %v109
  %v112 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 0
  store i32 3, i32* %v112
  %v116 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 1
  store i32 3, i32* %v116
  %v120 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 2
  store i32 9, i32* %v120
  %v124 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 3
  store i32 0, i32* %v124
  %v128 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 4
  store i32 0, i32* %v128
  %v132 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 5
  store i32 1, i32* %v132
  %v136 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 6
  store i32 1, i32* %v136
  %v140 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 7
  store i32 5, i32* %v140
  %v144 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 8
  store i32 7, i32* %v144
  %v148 = getelementptr [10 x i32], [10 x i32]* %v88, i32 0, i32 9
  store i32 8, i32* %v148
  store i32 10, i32* %v84
  %v151 = load [10 x i32], [10 x i32]* %v88
  %v152 = load i32, i32* %v84
  %v153 = call i32 @maxArea([10 x i32] %v151, i32 %v152)
  store i32 %v153, i32* %v84
  %v154 = load i32, i32* %v84
  ret i32 %v154
}


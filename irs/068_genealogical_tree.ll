@map12 = global <{ [100 x i32] }> <{ [100 x i32] zeroinitializer }>
@indegree16 = global <{ [10 x i32] }> <{ [10 x i32] zeroinitializer }>
@queue20 = global <{ [10 x i32] }> <{ [10 x i32] zeroinitializer }>
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
define void @topo(i32 ) {
topo22:
  %v23 = alloca i32
  %v24 = alloca i32
  store i32 0, i32* %v24
  %v26 = alloca i32
  store i32 0, i32* %v26
  %v28 = alloca i32
  store i32 zeroinitializer, i32* %v28
  %v30 = alloca i32
  store i32 zeroinitializer, i32* %v30
  store i32 1, i32* %v28
  store i32 1, i32* %v30
  %v36 = load i32, i32* %v28
  %v37 = load i32, i32* %v23
  %bool_38 = icmp sle i32 %v36, %v37
  %bool_40 = icmp ne i1 %bool_38, false
  br i1 %bool_40, label %while_entry34, label %next_entry35
while_entry34:
  store i32 1, i32* %v30
  %v44 = load i32, i32* %v30
  %v45 = load i32, i32* %v23
  %bool_46 = icmp sle i32 %v44, %v45
  %bool_48 = icmp ne i1 %bool_46, false
  br i1 %bool_48, label %while_entry42, label %next_entry43
next_entry35:
  store i32 0, i32* %v28
  %v104 = load i32, i32* %v28
  %v105 = load i32, i32* %v23
  %bool_106 = icmp slt i32 %v104, %v105
  %bool_108 = icmp ne i1 %bool_106, false
  br i1 %bool_108, label %while_entry102, label %next_entry103
while_entry42:
  %v52 = load i32, i32* %v30
  %v53 = getelementptr [10 x i32], [10 x i32]* @indegree16, i32 0, i32 %v52
  %v54 = load i32, i32* %v53
  %bool_56 = icmp eq i32 %v54, 0
  br i1 %bool_56, label %if_true_entry49, label %next_entry51
next_entry43:
  %v61 = load i32, i32* %v26
  %v62 = getelementptr [10 x i32], [10 x i32]* @queue20, i32 0, i32 %v61
  %v63 = load i32, i32* %v24
  store i32 %v63, i32* %v62
  %v64 = load i32, i32* %v26
  %v66 = add nsw i32 %v64, 1
  store i32 %v66, i32* %v26
  %v67 = load i32, i32* %v24
  %v68 = getelementptr [10 x i32], [10 x i32]* @indegree16, i32 0, i32 %v67
  %v71 = sub nsw i32 0, 1
  store i32 %v71, i32* %v68
  store i32 1, i32* %v30
  %v75 = load i32, i32* %v30
  %v76 = load i32, i32* %v23
  %bool_77 = icmp sle i32 %v75, %v76
  %bool_79 = icmp ne i1 %bool_77, false
  br i1 %bool_79, label %while_entry73, label %next_entry74
if_true_entry49:
  %v57 = load i32, i32* %v30
  store i32 %v57, i32* %v24
  br label %next_entry35
next_entry51:
  %v58 = load i32, i32* %v30
  %v60 = add nsw i32 %v58, 1
  store i32 %v60, i32* %v30
  br i1 %bool_48, label %while_entry42, label %next_entry43
while_entry73:
  %v83 = load i32, i32* %v24
  %v84 = load i32, i32* %v30
  %v85 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @map12, i32 0, i32 %v83, i32 %v84
  %bool_87 = icmp ne i32* %v85, float 0.00000000
  br i1 %bool_87, label %if_true_entry80, label %next_entry82
next_entry74:
  %v98 = load i32, i32* %v28
  %v100 = add nsw i32 %v98, 1
  store i32 %v100, i32* %v28
  br i1 %bool_40, label %while_entry34, label %next_entry35
if_true_entry80:
  %v88 = load i32, i32* %v30
  %v89 = getelementptr [10 x i32], [10 x i32]* @indegree16, i32 0, i32 %v88
  %v90 = load i32, i32* %v30
  %v91 = getelementptr [10 x i32], [10 x i32]* @indegree16, i32 0, i32 %v90
  %v92 = load i32, i32* %v91
  %v94 = sub nsw i32 %v92, 1
  store i32 %v94, i32* %v89
  br label %next_entry82
next_entry82:
  %v95 = load i32, i32* %v30
  %v97 = add nsw i32 %v95, 1
  store i32 %v97, i32* %v30
  br i1 %bool_79, label %while_entry73, label %next_entry74
while_entry102:
  %v109 = load i32, i32* %v28
  %v110 = getelementptr [10 x i32], [10 x i32]* @queue20, i32 0, i32 %v109
  %v111 = load i32, i32* %v110
  call void @putint(i32 %v111)
  call void @putch(i32 10)
  %v115 = load i32, i32* %v28
  %v117 = add nsw i32 %v115, 1
  store i32 %v117, i32* %v28
  br i1 %bool_108, label %while_entry102, label %next_entry103
next_entry103:
  ret void
}
define i32 @main() {
main118:
  %v119 = alloca i32
  store i32 zeroinitializer, i32* %v119
  %v121 = alloca i32
  store i32 zeroinitializer, i32* %v121
  %v123 = alloca i32
  store i32 1, i32* %v123
  store i32 5, i32* %v119
  %v128 = load i32, i32* %v123
  %v129 = load i32, i32* %v119
  %bool_130 = icmp sle i32 %v128, %v129
  %bool_132 = icmp ne i1 %bool_130, false
  br i1 %bool_132, label %while_entry126, label %next_entry127
while_entry126:
  %v133 = call i32 @getint()
  store i32 %v133, i32* %v121
  %v136 = load i32, i32* %v121
  %bool_138 = icmp ne i32 %v136, 0
  %bool_140 = icmp ne i1 %bool_138, false
  br i1 %bool_140, label %while_entry134, label %next_entry135
next_entry127:
  %v156 = load i32, i32* %v119
  call void @topo(i32 %v156)
  ret i32 0
while_entry134:
  %v141 = load i32, i32* %v123
  %v142 = load i32, i32* %v121
  %v143 = getelementptr [10 x [10 x i32]], [10 x [10 x i32]]* @map12, i32 0, i32 %v141, i32 %v142
  store i32 1, i32* %v143
  %v145 = load i32, i32* %v121
  %v146 = getelementptr [10 x i32], [10 x i32]* @indegree16, i32 0, i32 %v145
  %v147 = load i32, i32* %v121
  %v148 = getelementptr [10 x i32], [10 x i32]* @indegree16, i32 0, i32 %v147
  %v149 = load i32, i32* %v148
  %v151 = add nsw i32 %v149, 1
  store i32 %v151, i32* %v146
  %v152 = call i32 @getint()
  store i32 %v152, i32* %v121
  br i1 %bool_140, label %while_entry134, label %next_entry135
next_entry135:
  %v153 = load i32, i32* %v123
  %v155 = add nsw i32 %v153, 1
  store i32 %v155, i32* %v123
  br i1 %bool_132, label %while_entry126, label %next_entry127
}


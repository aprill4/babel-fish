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
  %v12 = alloca [4 x [2 x i32]]
  %v17 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 0, i32 0
  store i32 zeroinitializer, i32* %v17
  %v20 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 0, i32 1
  store i32 zeroinitializer, i32* %v20
  %v23 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 1, i32 0
  store i32 zeroinitializer, i32* %v23
  %v26 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 1, i32 1
  store i32 zeroinitializer, i32* %v26
  %v29 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 2, i32 0
  store i32 zeroinitializer, i32* %v29
  %v32 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 2, i32 1
  store i32 zeroinitializer, i32* %v32
  %v35 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 3, i32 0
  store i32 zeroinitializer, i32* %v35
  %v38 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 3, i32 1
  store i32 zeroinitializer, i32* %v38
  %v49 = alloca [4 x [2 x i32]]
  %v54 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 0, i32 0
  store i32 1, i32* %v54
  %v57 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 0, i32 1
  store i32 2, i32* %v57
  %v60 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 1, i32 0
  store i32 3, i32* %v60
  %v63 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 1, i32 1
  store i32 4, i32* %v63
  %v66 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 2, i32 0
  store i32 5, i32* %v66
  %v69 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 2, i32 1
  store i32 6, i32* %v69
  %v72 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 3, i32 0
  store i32 7, i32* %v72
  %v75 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v49, i32 0, i32 3, i32 1
  store i32 8, i32* %v75
  %v86 = alloca [4 x [2 x i32]]
  %v91 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 0, i32 0
  store i32 1, i32* %v91
  %v94 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 0, i32 1
  store i32 2, i32* %v94
  %v97 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 1, i32 0
  store i32 3, i32* %v97
  %v100 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 1, i32 1
  store i32 4, i32* %v100
  %v103 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 2, i32 0
  store i32 5, i32* %v103
  %v106 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 2, i32 1
  store i32 6, i32* %v106
  %v109 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 3, i32 0
  store i32 7, i32* %v109
  %v112 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 3, i32 1
  store i32 8, i32* %v112
  %v123 = alloca [4 x [2 x i32]]
  %v128 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 0, i32 0
  store i32 1, i32* %v128
  %v131 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 0, i32 1
  store i32 2, i32* %v131
  %v134 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 1, i32 0
  store i32 3, i32* %v134
  %v137 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 1, i32 1
  store i32 zeroinitializer, i32* %v137
  %v140 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 2, i32 0
  store i32 5, i32* %v140
  %v143 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 2, i32 1
  store i32 zeroinitializer, i32* %v143
  %v146 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 3, i32 0
  store i32 7, i32* %v146
  %v149 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 3, i32 1
  store i32 8, i32* %v149
  %v156 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v123, i32 0, i32 2, i32 1
  %v161 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v86, i32 0, i32 2, i32 1
  %v168 = alloca [4 x [2 x i32]]
  %v173 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 0, i32 0
  %v174 = load i32, i32* %v156
  store i32 %v174, i32* %v173
  %v177 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 0, i32 1
  %v178 = load i32, i32* %v161
  store i32 %v178, i32* %v177
  %v181 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 1, i32 0
  store i32 3, i32* %v181
  %v184 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 1, i32 1
  store i32 4, i32* %v184
  %v187 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 2, i32 0
  store i32 5, i32* %v187
  %v190 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 2, i32 1
  store i32 6, i32* %v190
  %v193 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 3, i32 0
  store i32 7, i32* %v193
  %v196 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 3, i32 1
  store i32 8, i32* %v196
  %v201 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 3, i32 1
  %v202 = load i32, i32* %v201
  %v207 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 0, i32 0
  %v208 = load i32, i32* %v207
  %v209 = add nsw i32 %v202, %v208
  %v214 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v168, i32 0, i32 0, i32 1
  %v215 = load i32, i32* %v214
  %v216 = add nsw i32 %v209, %v215
  %v221 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v12, i32 0, i32 2, i32 0
  %v222 = load i32, i32* %v221
  %v223 = add nsw i32 %v216, %v222
  ret i32 %v223
}


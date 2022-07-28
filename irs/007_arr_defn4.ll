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
  %v18 = alloca [4 x [2 x i32]]
  %v23 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 0, i32 0
  store i32 1, i32* %v23
  %v26 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 0, i32 1
  store i32 2, i32* %v26
  %v29 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 1, i32 0
  store i32 3, i32* %v29
  %v32 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 1, i32 1
  store i32 4, i32* %v32
  %v35 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 2, i32 0
  store i32 zeroinitializer, i32* %v35
  %v38 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 2, i32 1
  store i32 zeroinitializer, i32* %v38
  %v41 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 3, i32 0
  store i32 7, i32* %v41
  %v44 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 3, i32 1
  store i32 zeroinitializer, i32* %v44
  %v45 = alloca i32
  store i32 3, i32* %v45
  %v51 = alloca [4 x [2 x i32]]
  %v56 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 0, i32 0
  store i32 zeroinitializer, i32* %v56
  %v59 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 0, i32 1
  store i32 zeroinitializer, i32* %v59
  %v62 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 1, i32 0
  store i32 zeroinitializer, i32* %v62
  %v65 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 1, i32 1
  store i32 zeroinitializer, i32* %v65
  %v68 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 2, i32 0
  store i32 zeroinitializer, i32* %v68
  %v71 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 2, i32 1
  store i32 zeroinitializer, i32* %v71
  %v74 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 3, i32 0
  store i32 zeroinitializer, i32* %v74
  %v77 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v51, i32 0, i32 3, i32 1
  store i32 zeroinitializer, i32* %v77
  %v88 = alloca [4 x [2 x i32]]
  %v93 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 0, i32 0
  store i32 1, i32* %v93
  %v96 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 0, i32 1
  store i32 2, i32* %v96
  %v99 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 1, i32 0
  store i32 3, i32* %v99
  %v102 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 1, i32 1
  store i32 4, i32* %v102
  %v105 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 2, i32 0
  store i32 5, i32* %v105
  %v108 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 2, i32 1
  store i32 6, i32* %v108
  %v111 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 3, i32 0
  store i32 7, i32* %v111
  %v114 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 3, i32 1
  store i32 8, i32* %v114
  %v128 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v18, i32 0, i32 3, i32 0
  %v130 = alloca [4 x [2 x i32]]
  %v135 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 0, i32 0
  store i32 1, i32* %v135
  %v138 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 0, i32 1
  store i32 2, i32* %v138
  %v141 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 1, i32 0
  store i32 3, i32* %v141
  %v144 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 1, i32 1
  store i32 zeroinitializer, i32* %v144
  %v147 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 2, i32 0
  store i32 5, i32* %v147
  %v150 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 2, i32 1
  store i32 zeroinitializer, i32* %v150
  %v153 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 3, i32 0
  %v154 = load i32, i32* %v128
  store i32 %v154, i32* %v153
  %v157 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 3, i32 1
  store i32 8, i32* %v157
  %v165 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 2, i32 1
  %v170 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v88, i32 0, i32 2, i32 1
  %v177 = alloca [4 x [2 x [1 x i32]]]
  %v184 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 0, i32 0, i32 0
  %v185 = load i32, i32* %v165
  store i32 %v185, i32* %v184
  %v189 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 0, i32 1, i32 0
  %v190 = load i32, i32* %v170
  store i32 %v190, i32* %v189
  %v194 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 1, i32 0, i32 0
  store i32 3, i32* %v194
  %v198 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 1, i32 1, i32 0
  store i32 4, i32* %v198
  %v202 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 2, i32 0, i32 0
  store i32 5, i32* %v202
  %v206 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 2, i32 1, i32 0
  store i32 6, i32* %v206
  %v210 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 3, i32 0, i32 0
  store i32 7, i32* %v210
  %v214 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 3, i32 1, i32 0
  store i32 8, i32* %v214
  %v221 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 3, i32 1, i32 0
  %v222 = load i32, i32* %v221
  %v229 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 0, i32 0, i32 0
  %v230 = load i32, i32* %v229
  %v231 = add nsw i32 %v222, %v230
  %v238 = getelementptr [4 x [2 x [1 x i32]]], [4 x [2 x [1 x i32]]]* %v177, i32 0, i32 0, i32 1, i32 0
  %v239 = load i32, i32* %v238
  %v240 = add nsw i32 %v231, %v239
  %v245 = getelementptr [4 x [2 x i32]], [4 x [2 x i32]]* %v130, i32 0, i32 3, i32 0
  %v246 = load i32, i32* %v245
  %v247 = add nsw i32 %v240, %v246
  ret i32 %v247
}


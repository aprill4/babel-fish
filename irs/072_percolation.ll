@array11 = global <{ [110 x i32] }> <{ [110 x i32] zeroinitializer }>
@n13 = global i32 zeroinitializer
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
define void @init(i32 ) {
init15:
  %v16 = alloca i32
  %v17 = alloca i32
  store i32 1, i32* %v17
  %v21 = load i32, i32* %v17
  %v22 = load i32, i32* %v16
  %v23 = load i32, i32* %v16
  %v24 = mul i32 %v22, %v23
  %v26 = add nsw i32 %v24, 1
  %bool_27 = icmp sle i32 %v21, %v26
  %bool_29 = icmp ne i1 %bool_27, false
  br i1 %bool_29, label %while_entry19, label %next_entry20
while_entry19:
  %v30 = load i32, i32* %v17
  %v31 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v30
  %v34 = sub nsw i32 0, 1
  store i32 %v34, i32* %v31
  %v35 = load i32, i32* %v17
  %v37 = add nsw i32 %v35, 1
  store i32 %v37, i32* %v17
  br i1 %bool_29, label %while_entry19, label %next_entry20
next_entry20:
  ret void
}
define i32 @findfa(i32 ) {
findfa39:
  %v40 = alloca i32
  %v44 = load i32, i32* %v40
  %v45 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v44
  %v46 = load i32, i32* %v45
  %v47 = load i32, i32* %v40
  %bool_48 = icmp eq i32 %v46, %v47
  br i1 %bool_48, label %if_true_entry41, label %if_false_entry42
if_true_entry41:
  %v49 = load i32, i32* %v40
  ret i32 %v49
if_false_entry42:
  %v50 = load i32, i32* %v40
  %v51 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v50
  %v52 = load i32, i32* %v40
  %v53 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v52
  %v54 = load i32, i32* %v53
  %v55 = call i32 @findfa(i32 %v54)
  store i32 %v55, i32* %v51
  %v56 = load i32, i32* %v40
  %v57 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v56
  %v58 = load i32, i32* %v57
  ret i32 %v58
next_entry43:
  ret i32 zeroinitializer
}
define void @mmerge(i32 , i32 ) {
mmerge62:
  %v63 = alloca i32
  %v64 = alloca i32
  %v65 = alloca i32
  %v66 = load i32, i32* %v63
  %v67 = call i32 @findfa(i32 %v66)
  store i32 %v67, i32* %v65
  %v68 = alloca i32
  %v69 = load i32, i32* %v64
  %v70 = call i32 @findfa(i32 %v69)
  store i32 %v70, i32* %v68
  %v74 = load i32, i32* %v65
  %v75 = load i32, i32* %v68
  %bool_76 = icmp ne i32 %v74, %v75
  br i1 %bool_76, label %if_true_entry71, label %next_entry73
if_true_entry71:
  %v77 = load i32, i32* %v65
  %v78 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v77
  %v79 = load i32, i32* %v68
  store i32 %v79, i32* %v78
  br label %next_entry73
next_entry73:
  ret void
}
define i32 @main() {
main80:
  %v81 = alloca i32
  store i32 zeroinitializer, i32* %v81
  %v83 = alloca i32
  store i32 zeroinitializer, i32* %v83
  %v85 = alloca i32
  store i32 zeroinitializer, i32* %v85
  %v87 = alloca i32
  store i32 zeroinitializer, i32* %v87
  store i32 1, i32* %v81
  %bool_93 = icmp ne i32* %v81, float 0.00000000
  br i1 %bool_93, label %while_entry90, label %next_entry91
while_entry90:
  %v94 = load i32, i32* %v81
  %v96 = sub nsw i32 %v94, 1
  store i32 %v96, i32* %v81
  store i32 4, i32* @n13
  store i32 10, i32* %v83
  %v99 = alloca i32
  store i32 0, i32* %v99
  %v101 = alloca i32
  store i32 0, i32* %v101
  %v103 = load i32, i32* @n13
  call void @init(i32 %v103)
  %v105 = alloca i32
  %v106 = load i32, i32* @n13
  %v107 = load i32, i32* @n13
  %v108 = mul i32 %v106, %v107
  %v110 = add nsw i32 %v108, 1
  store i32 %v110, i32* %v105
  %v113 = load i32, i32* %v99
  %v114 = load i32, i32* %v83
  %bool_115 = icmp slt i32 %v113, %v114
  %bool_117 = icmp ne i1 %bool_115, false
  br i1 %bool_117, label %while_entry111, label %next_entry112
next_entry91:
  ret i32 0
while_entry111:
  %v118 = call i32 @getint()
  store i32 %v118, i32* %v85
  %v119 = call i32 @getint()
  store i32 %v119, i32* %v87
  %v123 = load i32, i32* %v101
  %bool_125 = icmp ne i32 %v123, zeroinitializer
  %bool_127 = icmp eq i1 %bool_125, zeroinitializer
  br i1 %bool_127, label %if_true_entry120, label %next_entry122
next_entry112:
  %v316 = load i32, i32* %v101
  %bool_318 = icmp ne i32 %v316, zeroinitializer
  %bool_320 = icmp eq i1 %bool_318, zeroinitializer
  br i1 %bool_320, label %if_true_entry313, label %next_entry315
if_true_entry120:
  %v128 = alloca i32
  %v129 = load i32, i32* @n13
  %v130 = load i32, i32* %v85
  %v132 = sub nsw i32 %v130, 1
  %v133 = mul i32 %v129, %v132
  %v134 = load i32, i32* %v87
  %v135 = add nsw i32 %v133, %v134
  store i32 %v135, i32* %v128
  %v136 = load i32, i32* %v128
  %v137 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v136
  %v138 = load i32, i32* %v128
  store i32 %v138, i32* %v137
  %v142 = load i32, i32* %v85
  %bool_144 = icmp eq i32 %v142, 1
  br i1 %bool_144, label %if_true_entry139, label %next_entry141
next_entry122:
  %v310 = load i32, i32* %v99
  %v312 = add nsw i32 %v310, 1
  store i32 %v312, i32* %v99
  br i1 %bool_117, label %while_entry111, label %next_entry112
if_true_entry139:
  %v147 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 0
  store i32 0, i32* %v147
  %v149 = load i32, i32* %v128
  call void @mmerge(i32 %v149, i32 0)
  br label %next_entry141
next_entry141:
  %v155 = load i32, i32* %v85
  %v156 = load i32, i32* @n13
  %bool_157 = icmp eq i32 %v155, %v156
  br i1 %bool_157, label %if_true_entry152, label %next_entry154
if_true_entry152:
  %v158 = load i32, i32* %v105
  %v159 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v158
  %v160 = load i32, i32* %v105
  store i32 %v160, i32* %v159
  %v161 = load i32, i32* %v128
  %v162 = load i32, i32* %v105
  call void @mmerge(i32 %v161, i32 %v162)
  br label %next_entry154
next_entry154:
  %v169 = load i32, i32* %v87
  %v170 = load i32, i32* @n13
  %bool_171 = icmp slt i32 %v169, %v170
  %bool_173 = icmp ne i1 %bool_171, zeroinitializer
  br i1 %bool_173, label %l167, label %r168
if_true_entry164:
  %v185 = load i32, i32* %v128
  %v186 = load i32, i32* %v128
  %v188 = add nsw i32 %v186, 1
  call void @mmerge(i32 %v185, i32 %v188)
  br label %next_entry166
next_entry166:
  %v195 = load i32, i32* %v87
  %bool_197 = icmp sgt i32 %v195, 1
  %bool_199 = icmp ne i1 %bool_197, zeroinitializer
  br i1 %bool_199, label %l193, label %r194
l167:
  %v174 = load i32, i32* %v128
  %v176 = add nsw i32 %v174, 1
  %v177 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v176
  %v178 = load i32, i32* %v177
  %v181 = sub nsw i32 0, 1
  %bool_182 = icmp ne i32 %v178, %v181
  %bool_184 = icmp ne i1 %bool_182, zeroinitializer
  br i1 %bool_184, label %if_true_entry164, label %r168
r168:
  br label %next_entry112
if_true_entry190:
  %v211 = load i32, i32* %v128
  %v212 = load i32, i32* %v128
  %v214 = sub nsw i32 %v212, 1
  call void @mmerge(i32 %v211, i32 %v214)
  br label %next_entry192
next_entry192:
  %v221 = load i32, i32* %v85
  %v222 = load i32, i32* @n13
  %bool_223 = icmp slt i32 %v221, %v222
  %bool_225 = icmp ne i1 %bool_223, zeroinitializer
  br i1 %bool_225, label %l219, label %r220
l193:
  %v200 = load i32, i32* %v128
  %v202 = sub nsw i32 %v200, 1
  %v203 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v202
  %v204 = load i32, i32* %v203
  %v207 = sub nsw i32 0, 1
  %bool_208 = icmp ne i32 %v204, %v207
  %bool_210 = icmp ne i1 %bool_208, zeroinitializer
  br i1 %bool_210, label %if_true_entry190, label %r194
r194:
  br label %next_entry112
if_true_entry216:
  %v237 = load i32, i32* %v128
  %v238 = load i32, i32* %v128
  %v239 = load i32, i32* @n13
  %v240 = add nsw i32 %v238, %v239
  call void @mmerge(i32 %v237, i32 %v240)
  br label %next_entry218
next_entry218:
  %v247 = load i32, i32* %v85
  %bool_249 = icmp sgt i32 %v247, 1
  %bool_251 = icmp ne i1 %bool_249, zeroinitializer
  br i1 %bool_251, label %l245, label %r246
l219:
  %v226 = load i32, i32* %v128
  %v227 = load i32, i32* @n13
  %v228 = add nsw i32 %v226, %v227
  %v229 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v228
  %v230 = load i32, i32* %v229
  %v233 = sub nsw i32 0, 1
  %bool_234 = icmp ne i32 %v230, %v233
  %bool_236 = icmp ne i1 %bool_234, zeroinitializer
  br i1 %bool_236, label %if_true_entry216, label %r220
r220:
  br label %next_entry112
if_true_entry242:
  %v263 = load i32, i32* %v128
  %v264 = load i32, i32* %v128
  %v265 = load i32, i32* @n13
  %v266 = sub nsw i32 %v264, %v265
  call void @mmerge(i32 %v263, i32 %v266)
  br label %next_entry244
next_entry244:
  %v277 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 0
  %v278 = load i32, i32* %v277
  %v281 = sub nsw i32 0, 1
  %bool_282 = icmp ne i32 %v278, %v281
  %bool_284 = icmp ne i1 %bool_282, zeroinitializer
  br i1 %bool_284, label %l273, label %r274
l245:
  %v252 = load i32, i32* %v128
  %v253 = load i32, i32* @n13
  %v254 = sub nsw i32 %v252, %v253
  %v255 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v254
  %v256 = load i32, i32* %v255
  %v259 = sub nsw i32 0, 1
  %bool_260 = icmp ne i32 %v256, %v259
  %bool_262 = icmp ne i1 %bool_260, zeroinitializer
  br i1 %bool_262, label %if_true_entry242, label %r246
r246:
  br label %next_entry112
if_true_entry268:
  store i32 1, i32* %v101
  %v302 = alloca i32
  %v303 = load i32, i32* %v99
  %v305 = add nsw i32 %v303, 1
  store i32 %v305, i32* %v302
  %v306 = load i32, i32* %v302
  call void @putint(i32 %v306)
  call void @putch(i32 10)
  br label %next_entry270
next_entry270:
  br label %next_entry122
l271:
  %v295 = call i32 @findfa(i32 0)
  %v296 = load i32, i32* %v105
  %v297 = call i32 @findfa(i32 %v296)
  %bool_298 = icmp eq i32 %v295, %v297
  %bool_300 = icmp ne i1 %bool_298, zeroinitializer
  br i1 %bool_300, label %if_true_entry268, label %r272
r272:
  br label %next_entry112
l273:
  %v285 = load i32, i32* %v105
  %v286 = getelementptr [110 x i32], [110 x i32]* @array11, i32 0, i32 %v285
  %v287 = load i32, i32* %v286
  %v290 = sub nsw i32 0, 1
  %bool_291 = icmp ne i32 %v287, %v290
  %bool_293 = icmp ne i1 %bool_291, zeroinitializer
  br i1 %bool_293, label %l271, label %r274
r274:
  br label %next_entry270
if_true_entry313:
  %v323 = sub nsw i32 0, 1
  call void @putint(i32 %v323)
  call void @putch(i32 10)
  br label %next_entry315
next_entry315:
  br i1 %bool_93, label %while_entry90, label %next_entry91
}


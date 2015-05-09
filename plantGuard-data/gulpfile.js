var gulp = require('gulp');
var sass = require('gulp-sass');
var sourcemaps = require('gulp-sourcemaps');

gulp.task('sass', function() {
	console.log("wasdasd");
	gulp.src('.scss/*.scss')
		.pipe(sass().on('error', sass.logError))
		.pipe(gulp.dest('./css'));
});

gulp.task('default', ['sass']);
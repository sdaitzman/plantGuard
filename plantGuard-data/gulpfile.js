var gulp = require('gulp'),
	gutil = require('gulp-util'),
	sass = require('gulp-sass'),
	autoprefixer = require('gulp-autoprefixer'),
	minifycss = require('gulp-minify-css'),
	coffee = require('gulp-coffee'),
	jshint = require('gulp-jshint'),
	uglify = require('gulp-uglify'),
	imagemin = require('gulp-imagemin'),
	rename = require('gulp-rename'),
	concat = require('gulp-concat'),
	notify = require('gulp-notify'),
	cache = require('gulp-cache'),
	livereload = require('gulp-livereload');
	sourcemaps = require('gulp-sourcemaps'),
	watch = require('gulp-watch');

gulp.task('styles', function() {
	return gulp.src('./scss/*.scss')
		.pipe(sourcemaps.init())
			.pipe(sass().on('error', sass.logError))
			.pipe(autoprefixer('last 2 version', 'safari 5', 'ie 8', 'ie 9', 'opera 12.1', 'ios 6', 'android 4'))
			.pipe(rename({suffix: '.min'}))
			.pipe(minifycss())
		.pipe(sourcemaps.write())
		.pipe(gulp.dest('./css'))
		.pipe(notify({ message: 'Styles task is complete' }));
});

gulp.task('scripts', function() {
	return gulp.src('./coffee/*.coffee')
		.pipe(sourcemaps.init())
			.pipe(coffee({bare: true}).on('error', gutil.log))
			// .pipe(uglify())
			.pipe(rename({suffix: '.min'}))
		.pipe(sourcemaps.write())
		.pipe(gulp.dest('./js'))
		.pipe(notify({ message: 'Coffee task is complete' }));
});

gulp.task('watch', function() {
	gulp.watch('./scss/*.scss', ['styles']);
	gulp.watch('./coffee/*.coffee', ['scripts']);
});


gulp.task('default', ['styles', 'scripts', 'watch']);
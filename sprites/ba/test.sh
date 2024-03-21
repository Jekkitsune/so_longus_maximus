for image in *.png; do
	echo $image
	convert $image -resize 200x200! out/$image&
done

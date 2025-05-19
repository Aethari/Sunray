-- A simple script to generate empty text maps quickly
-- 2025 Aethari

continue = "y"

while(continue == "y") do
	io.write("Enter the name for your map: ")
	name = io.read()

	io.write("\nDo you want to generate borders at the edges of your map (does not affect map size) (y/n)? ")
	input = io.read()

	if(string.lower(input) == "y") then
		genBorders = true
	else
		genBorders = false
	end

	io.write("\nEnter the character used for empty space: ")
	emptyChar = io.read()

	io.write("Enter the character used for walls: ")
	fillChar = io.read()

	io.write("\nDo you want your map to be square (y/n): ")
	input = io.read()

	if(string.lower(input) == "y") then
		isSquare = true
	else
		isSquare = false
	end

	if(isSquare) then
		io.write("Enter the size of the map: ")
		size = tonumber(io.read())

		--generate the map
		map = {}

		for y=1, size do
			map[y] = {}

			for x=1, size do
				if(genBorders) then
					if(x==1 or x==size or y==1 or y==size) then
						map[y][x] = fillChar
					else
						map[y][x] = emptyChar
					end
				else
					map[y][x] = emptyChar
				end
			end
		end

		--write the map to the output file
		outfile = io.open(""..name..".txt", "w")

		for y=1, #map do
			for x=1, #map[y] do
				outfile:write(","..map[y][x])
			end
			outfile:write("\n")
		end

		outfile:close()
	else
		io.write("Enter the width of the map: ")
		width = tonumber(io.read())
		io.write("Enter the height of the map: ")
		height = tonumber(io.read())

		--generate the map
		map = {}

		for y=1, height do
			map[y] = {}

			for x=1, width do
				if(genBorders) then
					if(x==1 or x==width or y==1 or y==height) then
						map[y][x] = fillChar
					else
						map[y][x] = emptyChar
					end
				else
					map[y][x] = emptyChar
				end
			end
		end

		--print the map
		outfile = io.open(""..name..".txt", "w")

		for y=1, #map do
			for x=1, #map[y] do
				outfile:write(","..map[y][x])
			end
			outfile:write("\n")
		end

		outfile:close()
	end

	io.write("\nYour map has been successfuly generated in "..name..".txt")
	io.write("\nDo you want to generate another map (y/n)? ")
	continue = io.read()
end

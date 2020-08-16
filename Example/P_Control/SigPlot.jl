using Plots
using CSV

gr(show = true)

function main()

	# graph setting
	Title = "P Control"
	Label = ["reference" "Vo" "V1"]
    XLabel = "Time (s)"
    YLabel = "Voltage (V)"
	# sampling time
	dt = 0.1
	# graph width(number of plotting point)
	width = 100
	# declear x, y
	x = dt:dt:dt*width
	y = zeros(width,3)
	x_offset = 0

	for i in 1:1000
		data = CSV.read("data.csv",header=false)
		datalen = length(data.Column1)
		if datalen <= width
			y[1:datalen,1:3] = [data.Column1 data.Column2 data.Column3]
		else
			y = [data.Column1[end-(width-1):end] data.Column2[end-(width-1):end] data.Column3[end-(width-1):end]]
			x_offset = dt*(datalen-width)
		end	
    	display(plot(x + x_offset*ones(width,1),y,title = Title,label = Label,xlabel=XLabel,ylabel=YLabel))
	end
end

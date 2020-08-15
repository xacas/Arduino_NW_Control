using Plots
using CSV

gr(show = true)

function main()

	# graph setting
	Title = "time-series data"
	Label = "random data"
    XLabel = "time (s)"
    YLabel = "number"
	# sampling time
	dt = 0.1
	# graph width(number of plotting point)
	width = 100
	# declear x, y
	x = dt:dt:dt*width
	y = zeros(width,1)
	x_offset = 0

	for i in 1:5000
		data = CSV.read("data.csv",header=false)
		datalen = length(data.Column1)
		if datalen <= width
			y[1:datalen] = data.Column1
		else
			y = data.Column1[end-(width-1):end]
			x_offset = dt*(datalen-width)
		end	
    	display(plot(x + x_offset*ones(width,1),y,title = Title,label = Label,xlabel=XLabel,ylabel=YLabel))
	end
end

using Plots
using CSV

gr(show = true)

function main()

	# graph setting
	Title = "Integral Servo Control"
	Label = ["reference" "Vo" "V1"]
    XLabel = "Time (s)"
    YLabel = "Voltage (V)"
    YLimit = (-3,3)
	# sampling time
	dt = 0.1
	# graph width(number of plotting point)
	width = 300
	# declear x, y
	x = dt:dt:dt*width
	y = zeros(width,3)
	x_offset = 0

	for i in 1:2000
		data = CSV.read("data.csv",header=false)
		datalen = length(data[!,1])
		if datalen <= width
			y[1:datalen,1:3] = Matrix(data)
		else
			y = Matrix(data[end-(width-1):end,1:3])
			x_offset = dt*(datalen-width)
		end	
    	display(plot(x + x_offset*ones(width,1),y,
    	title = Title,label = Label,xlabel = XLabel,ylabel = YLabel,ylims = YLimit))
	end
end

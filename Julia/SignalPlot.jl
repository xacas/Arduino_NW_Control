using Plots
using CSV

gr(show = false)

function main()

	# graph setting
	Title = basename(pwd())
	OLabel = ["reference" "Vo" "V1"]
	ILabel = [ "Vi" ]
	ODim = length(OLabel)
	Dim = ODim+length(ILabel)
	XLabel = "Time (s)"
	YLabel = "Voltage (V)"
	YLimit = (-3,3)
	# sampling time
	dt = 0.1
	# graph width(number of plotting point)
	width = 300
	# declear x, y
	x = dt:dt:dt*width
	y = zeros(width,Dim)
	x_offset = 0

	for i in 1:2000
		data = CSV.read("data.csv",header=false)
		datalen = length(data[!,1])
		if datalen <= width
			y[1:datalen,1:Dim] = Matrix(data)
		else
			y = Matrix(data[end-(width-1):end,1:Dim])
			x_offset = dt*(datalen-width)
		end
		p1=plot(x + x_offset*ones(width,1),y[1:end,1:ODim],
		title = Title*" Output",label = OLabel)
		p2=plot(x + x_offset*ones(width,1),y[1:end,ODim+1:end],
		title = Title*" Input",label = ILabel[1])
		display(plot(p1,p2,layout=(2,1),
		xlabel = XLabel,ylabel = YLabel,ylims = YLimit))
	end
end

using Plots
using CSV

gr(show = false)

function main()

	# graph setting
	Title = basename(pwd())
	OLabel = ["V1" "Vo" "reference"]
	ILabel = [ "Vi" ]
	ODim = length(OLabel)
	Dim = ODim+length(ILabel)
	XLabel = "Time (s)"
	YLabel = "Voltage (V)"
	YLimit = (-2.5,2.5)
	# sampling time
	dt = 0.1
	# graph width(number of plotting point)
	width = 3000
	# declear x, y
	x = dt:dt:dt*width
	y = zeros(width,Dim)

	data = CSV.read("data.csv",header=false)
	datalen = length(data[!,1])
	if datalen <= width
		y[1:datalen,1:Dim] = Matrix(data)
	else
		y = Matrix(data[1:width,1:Dim])
	end
	p1=plot(x,y[1:end,ODim:-1:1],title = Title*" Output",label = OLabel,lw = [2 2 1],legend=:bottomleft,line=([:solid :solid :dash]))
	p2=plot(x,y[1:end,ODim+1:end],title = Title*" Input",label = ILabel[1],lw = 2,legend=:bottomleft)
	display(plot(p1,p2,layout=(2,1),
	xlabel = XLabel,ylabel = YLabel,ylims = YLimit))
end



xchannel=RemoteChannel(()->Channel{Int}(32))
uchannel=RemoteChannel(()->Channel{Int}(32))


kalman=@spawn begin

  while true
  x=10
  put!(xchannel,x)
  u=take!(uchannel)
  println("on kalman",u)
  sleep(1)
  end

end


MPC=@spawn begin

  while true
  xhat=take!(xchannel)
  put!(uchannel,3)
  println("on MPC",xhat)
  sleep(1)
  end
end




@everywhere we_should_run=true
xchannel=RemoteChannel(()->Channel{Tuple}(2));
uchannel=RemoteChannel(()->Channel{Int}(2));
  Su=ReentrantLock()
  Sx=ReentrantLock()
#  Su=Mutex()
#  Sx=Mutex()
kalman=@spawnat 1 begin
  #initialize
  x=[0.0 0.0];
  put!(xchannel,(0,0))
  put!(uchannel,0)


  while we_should_run         #start loop

    x=x+[1 1]

    lock(Su)
      if isready(uchannel)
        u=take!(uchannel)
      end
    unlock(Su)

    lock(Sx)
      while isready(xchannel) #empty channel. only last result should be stored
        take!(xchannel)
      end
      put!(xchannel,(x[1],x[2]))
    unlock(Sx)

    println("on kalman, u= ",u)
    sleep(0.5)
  end

end


MPC=@spawnat 2 begin
  #initialize
  u=0
  x_hat=[0 0]
  put!(xchannel,(0,0))
  put!(uchannel,0)



  while we_should_run         #start loop

    u=u+1
    lock(Sx)
      if isready(xchannel)
        x_hat[1],x_hat[2]=take!(xchannel)
      end
    unlock(Sx)

    lock(Su)
      while isready(uchannel) #empty channel. only last result should be stored
        take!(uchannel)
      end
      put!(uchannel,u)
    unlock(Su)

    println("on MPC, x_hat=  ",x_hat)

    sleep(1)
  end
end

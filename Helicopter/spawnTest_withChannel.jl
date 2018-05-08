


@everywhere we_should_run=true
xchannel=RemoteChannel(()->Channel{Int}(2));
uchannel=RemoteChannel(()->Channel{Int}(2));
  Su=ReentrantLock()
  Sx=ReentrantLock()
#  Su=Mutex()
#  Sx=Mutex()
kalman=@spawnat 1 begin
  x=0

  put!(xchannel,0)
  put!(uchannel,0)
  #Su=SpinLock()
  #Sx=SpinLock()
  we_should_run=true

  while we_should_run
    x=x+1

    lock(Su)
      if isready(uchannel)
        u=take!(uchannel)
      end
   unlock(Su)

    lock(Sx)
      while isready(xchannel) #empty channel. only last result should be stored
        take!(xchannel)
      end
      put!(xchannel,x)
    unlock(Sx)

    println("on kalman ",u)
    sleep(0.1)
  end

end


MPC=@spawnat 2 begin
  u=0

  put!(xchannel,0)
  put!(uchannel,0)
  #Su=ReentrantLock()
  #Sx=ReentrantLock()
  we_should_run=true

  while we_should_run
    u=u+1
    lock(Sx)
      if isready(xchannel)
        x_hat=take!(xchannel)
      end
    unlock(Sx)

    lock(Su)
      while isready(uchannel) #empty channel. only last result should be stored
        take!(uchannel)
      end
      put!(uchannel,u)
    unlock(Su)

    println("on MPC ",x_hat)

    sleep(0.2)
  end
end

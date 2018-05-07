

xchannel=Channel(32)
uchannel=Channel(32)
x=0
put!(xchannel,x)

u=0
put!(uchannel,u)
  Su=ReentrantLock()
  Sx=ReentrantLock()

kalman=@spawn begin
  x=0


  while true
    x=x+1

    lock(Su)
    if isready(uchannel)
      u=take!(uchannel)
    end
    unlock(Su)

    lock(Sx)
    while isready(xchannel)
      take!(xchannel)  #empty xchannel
    end
    put!(xchannel,x)
    unlock(Sx)

    println("on kalman ",u)
    sleep(0.1)
  end

end


MPC=@spawn begin
  u=0

  while true
    u=u+1
    lock(Sx)
    if isready(xchannel)
      xhat=take!(xchannel)
    end
    unlock(Sx)

    lock(Su)
    while isready(uchannel)
      take!(uchannel)         #empty uchannel
    end
    put!(uchannel,u)
    unlock(Su)
    println("on MPC ",xhat)
    sleep(0.2)
  end
end

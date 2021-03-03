function status = pageFaults(pageReq, nFrame)
% PAGEFAULTS - Compute number of page faults for LRU
%   
% STATUS = PAGEFAULTS( PAGERREQ, NFRAME ) simulates a Least
% Recenlty Used page reference policy with NFRAME number of
% frames. At each time step, the funciton is called with the next
% page request in PAGEREQ. The function returns either 'M' or 'H'
% if it was a miss or a hit, respectively. The function stores an
% internal state, using persistent variables, to store previously
% stored pages. At the beginning, consider every frame empty.

  persistent frames = zeros(nFrame , 1);
  % Check if the pageReq is in the frames array
  index = -1;
  result = 0;
  for i = 1:nFrame
    if(frames(i) == pageReq)
      index = i;
      result = 1;
      % Cycle the pages after the hit, since we will put the pageReq last, so there is a vacancy
      for j = i:(nFrame-1)
        frames(j) = frames(j+1);
      end
      frames(nFrame) = pageReq;
    endif
  end
  if (result == 0)
    % Cycle the frames
    for i = 1:(nFrame-1)
      frames(i) = frames(i+1);
    end
    frames(nFrame) = pageReq;
    status = 'M';
    return;
  else
    status = 'H';
    return;
  endif
  
  
  
end
